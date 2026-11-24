from pathlib import Path
import re
from xml.sax.saxutils import escape

from reportlab.lib import colors
from reportlab.lib.enums import TA_CENTER
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import mm
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, Preformatted, PageBreak, KeepTogether
)

ROOT = Path(__file__).resolve().parents[2]
SOURCE_DIR = ROOT / "reviewer"
OUTPUT_DIR = ROOT / "output" / "pdf"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

SOURCES = [
    "Module-1-Reviewer.md",
    "Module-2-Reviewer.md",
    "Module-3-Reviewer.md",
    "Module-4-Reviewer.md",
    "Final-Review-All-Modules.md",
    "OpenGL-GLUT-Syntax-Cheatsheet.md",
]

FONT = "/usr/share/fonts/google-noto/NotoSans-Regular.ttf"
FONT_BOLD = "/usr/share/fonts/google-noto/NotoSans-Bold.ttf"
MONO = "/usr/share/fonts/google-noto/NotoSansMono-Regular.ttf"
pdfmetrics.registerFont(TTFont("ReviewSans", FONT))
pdfmetrics.registerFont(TTFont("ReviewSans-Bold", FONT_BOLD))
pdfmetrics.registerFont(TTFont("ReviewMono", MONO))


def inline_markup(text: str) -> str:
    text = escape(text)
    text = re.sub(r"`([^`]+)`", r'<font name="ReviewMono">\1</font>', text)
    text = re.sub(r"\*\*([^*]+)\*\*", r'<b>\1</b>', text)
    return text


def footer(canvas, doc):
    canvas.saveState()
    canvas.setFont("ReviewSans", 8)
    canvas.setFillColor(colors.HexColor("#555555"))
    canvas.drawCentredString(A4[0] / 2, 10 * mm, f"Page {doc.page}")
    canvas.restoreState()


def styles():
    base = getSampleStyleSheet()
    return {
        "title": ParagraphStyle(
            "Title", parent=base["Title"], fontName="ReviewSans-Bold",
            fontSize=20, leading=24, alignment=TA_CENTER,
            textColor=colors.HexColor("#111111"), spaceAfter=12,
        ),
        "h2": ParagraphStyle(
            "H2", parent=base["Heading2"], fontName="ReviewSans-Bold",
            fontSize=14, leading=18, spaceBefore=13, spaceAfter=7,
            textColor=colors.HexColor("#111111"), keepWithNext=True,
        ),
        "h3": ParagraphStyle(
            "H3", parent=base["Heading3"], fontName="ReviewSans-Bold",
            fontSize=11.5, leading=15, spaceBefore=10, spaceAfter=5,
            textColor=colors.HexColor("#222222"), keepWithNext=True,
        ),
        "body": ParagraphStyle(
            "Body", parent=base["BodyText"], fontName="ReviewSans",
            fontSize=9.2, leading=13, spaceAfter=5,
            textColor=colors.HexColor("#111111"),
        ),
        "question": ParagraphStyle(
            "Question", parent=base["BodyText"], fontName="ReviewSans",
            fontSize=9.2, leading=13, leftIndent=4 * mm,
            firstLineIndent=-4 * mm, spaceBefore=4, spaceAfter=4,
        ),
        "bullet": ParagraphStyle(
            "Bullet", parent=base["BodyText"], fontName="ReviewSans",
            fontSize=9.2, leading=13, leftIndent=6 * mm,
            firstLineIndent=-3 * mm, spaceAfter=3,
        ),
        "code": ParagraphStyle(
            "Code", fontName="ReviewMono", fontSize=7.5, leading=10,
            leftIndent=5 * mm, rightIndent=5 * mm, spaceBefore=4, spaceAfter=7,
            backColor=colors.HexColor("#F3F3F3"), borderPadding=6,
            borderColor=colors.HexColor("#D8D8D8"), borderWidth=0.5,
        ),
    }


def parse_markdown(path: Path):
    st = styles()
    raw = path.read_text(encoding="utf-8")
    raw = (raw.replace("—", "-").replace("–", "-")
              .replace("→", "->").replace("←", "<-")
              .replace("×", "x"))
    lines = raw.splitlines()
    story = []
    paragraph = []
    in_code = False
    code = []

    def flush_paragraph():
        if paragraph:
            joined = " ".join(x.strip() for x in paragraph).strip()
            if joined:
                style = st["question"] if re.match(r"^\d+\.\s", joined) else st["body"]
                story.append(Paragraph(inline_markup(joined), style))
            paragraph.clear()

    for line in lines:
        if line.startswith("```"):
            flush_paragraph()
            if in_code:
                story.append(Preformatted("\n".join(code), st["code"] or None))
                code.clear()
                in_code = False
            else:
                in_code = True
            continue
        if in_code:
            code.append(line.replace("\t", "    "))
            continue
        if line.startswith("# "):
            flush_paragraph()
            if story:
                story.append(PageBreak())
            story.append(Paragraph(inline_markup(line[2:]), st["title"]))
        elif line.startswith("## "):
            flush_paragraph()
            story.append(Paragraph(inline_markup(line[3:]), st["h2"]))
        elif line.startswith("### "):
            flush_paragraph()
            story.append(Paragraph(inline_markup(line[4:]), st["h3"]))
        elif line.strip() == "---":
            flush_paragraph()
            story.append(Spacer(1, 5))
        elif re.match(r"^[-*] ", line):
            flush_paragraph()
            story.append(Paragraph("• " + inline_markup(line[2:]), st["bullet"]))
        elif line.startswith("|"):
            flush_paragraph()
            if set(line.replace("|", "").replace("-", "").replace(":", "").strip()) == set():
                continue
            cells = [c.strip() for c in line.strip("|").split("|")]
            story.append(Paragraph("  |  ".join(inline_markup(c) for c in cells), st["body"]))
        elif not line.strip():
            flush_paragraph()
        else:
            if re.match(r"^\d+\.\s", line) and paragraph:
                flush_paragraph()
            hard_break = line.endswith("  ")
            paragraph.append(line.rstrip())
            if hard_break:
                flush_paragraph()

    flush_paragraph()
    if code:
        story.append(Preformatted("\n".join(code), st["code"]))
    return story


def build(source_name: str):
    source = SOURCE_DIR / source_name
    output = OUTPUT_DIR / source.with_suffix(".pdf").name
    doc = SimpleDocTemplate(
        str(output), pagesize=A4,
        rightMargin=16 * mm, leftMargin=16 * mm,
        topMargin=15 * mm, bottomMargin=17 * mm,
        title=source.stem.replace("-", " "), author="Computer Graphics Reviewer",
    )
    doc.build(parse_markdown(source), onFirstPage=footer, onLaterPages=footer)
    return output


if __name__ == "__main__":
    for name in SOURCES:
        print(build(name))
