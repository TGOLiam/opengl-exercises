# CS0045 Computer Graphics and Visual Computing

Laboratory work for CS0045 using classic OpenGL and FreeGLUT. Each module contains guided examples, practice exercises, source code, and captured outputs.

## Modules

| Module | Topic | Resources |
| --- | --- | --- |
| 1 | Introduction to Computer Graphics | [Gallery](Module1/README.md) · [Completed manual](Module1/docs/SERRANO_PE_M1.docx) |
| 2 | OpenGL Primitives and Color | [Gallery](Module2/README.md) · [Student manual](Module2/docs/Module_02_Student_Laboratory_Manual.docx) · [Completed manual](Module2/docs/SERRANO_PE_M2.docx) |
| 3 | Text and Event-Driven Interaction | [Gallery](Module3/README.md) · [Student manual](Module3/docs/Module_03_Student_Laboratory_Manualv2.docx) · [Completed manual](Module3/docs/SERRANO_PE_M3.docx) |
| 4 | Vertex Arrays and Indexed Rendering | [Gallery](Module4/README.md) · [Student manual](Module4/docs/Module_04_Student_Laboratory_Manual%20%281%29.docx) · [Completed manual](Module4/docs/SERRANO_PE_M4.docx) |

## Run an Activity

From the repository root:

```sh
./run 1 e 2    # guided example 2
./run 1 m 3    # mini-exercise 3
./run 4 x 1    # Module 4 practice exercise 1
```

Use `e` for guided examples, `m` for mini-exercises, and `x` for practice exercises.

## Build a Module

```sh
make m1     # all Module 1 activities
make m2x    # Module 2 practice exercises
make m3     # all Module 3 activities
make m4x    # Module 4 practice exercises
```

Run `make help` for every available target. Builds are written to `build/ModuleN/`.

## Project Layout

```text
ModuleN/
├── example/          Guided programs
├── mini-exercises/   Short concept checks (where provided)
├── SERRANO_PE_*.cpp  Practice exercise solutions
├── assets/outputs/   Screenshots and GIF demonstrations
└── docs/             Student and completed manuals
```

Requirements: a C++17 compiler, GNU Make, OpenGL, GLU, and FreeGLUT.
