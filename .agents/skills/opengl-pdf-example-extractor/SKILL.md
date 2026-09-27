---
name: opengl-pdf-example-extractor
description: Gather Part A guided-example C++ code from an OpenGL course-module PDF at the beginning of a module task, stage one candidate per numbered example, verify PDF line-wrap repairs, and compile the resulting ModuleN/example sources. Use for manuals with Part A guided examples and Example NN headings; do not extract Part C answer-key solutions.
---

# OpenGL PDF Example Extractor

Gather the guided examples before implementing exercises or preparing module documentation. The manual is the source of truth.

## Start-of-task workflow

1. Locate the target module PDF and its `ModuleN/example/` directory.
2. Create a temporary staging directory outside the repository, normally with `mktemp -d`.
3. Run `scripts/stage_pdf_examples.py <manual.pdf> <staging-dir>`. It extracts only the text between Part A and Part B, writes `01.txt` through `20.txt`, and reports suspicious PDF wraps.
4. Compare each staged candidate with its Part A code block and the corresponding existing example source, if present.
5. Transcribe into `ModuleN/example/1.cpp` through `20.cpp` using the module's existing naming convention. Use `apply_patch`; never replace an existing source without checking its differences first.
6. Repair only presentation-induced PDF wrapping. Preserve include blocks, comments, identifiers, literals, callback registration, window titles, statement order, and formatting. Do not refactor or improve the examples.
7. Compile all guided examples with `make MODULE=N MODE=examples`. Stop and resolve any transcription error before continuing the main task.

## Boundaries

- Extract only Part A guided examples. Never substitute Part C practice-exercise answers.
- Treat staged files as candidates, not authoritative compilable sources. PDF extraction may split string literals, comments, identifiers, or statements across physical pages.
- Keep staging directories and extraction reports outside the repository.
- If Part A or the expected numbered examples cannot be detected, stop and report the exact missing structure rather than guessing boundaries.
