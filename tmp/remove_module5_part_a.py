from pathlib import Path

from docx import Document


manual = Path("Module5/docs/SERRANO_PE_M5.docx")
document = Document(manual)

for paragraph in document.paragraphs:
    if paragraph.text.strip() == "This manual has three parts:":
        paragraph.text = "This manual contains the practice exercises and answer key:"
    elif paragraph.text.strip().startswith("Part A — 20 worked Examples (Ex01–Ex20)."):
        paragraph._element.getparent().remove(paragraph._element)
    elif paragraph.text.strip() == "20 Guided Examples • 20 Practice Exercises":
        paragraph.text = "20 Practice Exercises"
    elif "(like Example 12)" in paragraph.text:
        paragraph.text = paragraph.text.replace(" (like Example 12)", "")

part_a = next(
    (
        paragraph._p
        for paragraph in document.paragraphs
        if paragraph.text.strip() == "Part A — Guided Examples (Ex01–Ex20)"
    ),
    None,
)
if part_a is not None:
    part_b = next(
        paragraph._p
        for paragraph in document.paragraphs
        if paragraph.text.strip() == "Part B — Practice Exercises (Q01–Q20)"
    )
    deleting = False
    for child in list(document.element.body):
        if child is part_a:
            deleting = True
        if child is part_b:
            break
        if deleting:
            document.element.body.remove(child)

document.save(manual)

checked = Document(manual)
texts = [paragraph.text.strip() for paragraph in checked.paragraphs]
assert "Part A — Guided Examples (Ex01–Ex20)" not in texts
assert not any(text.startswith("Part A — 20 worked Examples") for text in texts)
assert texts.count("Part B — Practice Exercises (Q01–Q20)") == 1
assert sum(text.startswith("Exercise ") for text in texts) == 20
