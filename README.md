# CS0045 Computer Graphics and Visual Computing

Laboratory work for CS0045 using classic OpenGL and FreeGLUT. Each module contains guided examples, practice exercises, source code, and captured outputs.

## Modules

| Module | Topic | Resources |
| --- | --- | --- |
| 1 | Introduction to Computer Graphics | [Gallery](Module1/README.md) · [Completed manual](Module1/docs/SERRANO_PE_M1.pdf) |
| 2 | OpenGL Primitives and Color | [Gallery](Module2/README.md) · [Completed manual](Module2/docs/SERRANO_PE_M2.pdf) |
| 3 | Text and Event-Driven Interaction | [Gallery](Module3/README.md) · [Completed manual](Module3/docs/SERRANO_PE_M3.pdf) |
| 4 | Vertex Arrays and Indexed Rendering | [Gallery](Module4/README.md) · [Completed manual](Module4/docs/SERRANO_PE_M4.pdf) |
| 5 | Advanced Rendering Techniques | [Gallery](Module5/README.md) · [Completed manual](Module5/docs/SERRANO_PE_M5.pdf) |
| 6 | Shaders and Modern OpenGL | [Gallery](Module6/README.md) · [Completed manual](Module6/docs/SERRANO_PE_M6.pdf) |
| 7 | 3D Modeling and Transformations | [Gallery](Module7/README.md) · [Completed manual](Module7/docs/SERRANO_PE_M7.pdf) |
| 8 | Final Project and Advanced Topics | [Gallery](Module8/README.md) · [Completed manual](Module8/docs/SERRANO_PE_M8.pdf) |

## Run an Activity

From the repository root:

```sh
./run 1e2      # Module 1, guided example 2
./run 1x1      # Module 1, practice exercise 1
./run 4x10     # Module 4, practice exercise 10
./run 8x20     # Module 8, practice exercise 20
```

Use `e` for guided examples and `x` for practice exercises.

## Build a Module

```sh
make m1     # all Module 1 activities
make m2x    # Module 2 practice exercises
make m3     # all Module 3 activities
make m4x    # Module 4 practice exercises
make m5     # all Module 5 activities
make m6x    # Module 6 practice exercises
make m7     # all Module 7 activities
make m8x    # Module 8 practice exercises
```

Run `make help` for every available target. Builds are written to `build/ModuleN/`.

## Project Layout

```text
ModuleN/
├── example/          Guided programs
├── SERRANO_PE_*.cpp  Practice exercise solutions
├── assets/           Tracked PE_* screenshots and GIF demonstrations
└── docs/             Completed manuals
```

Requirements: a C++17 compiler, GNU Make, OpenGL, GLU, and FreeGLUT.

## Documentation Skills

The repository includes specialized documentation skills for module preparation:
- `opengl-module-documentation`: Prepare complete module submissions with GIFs and embedded media
- `opengl-pdf-example-extractor`: Extract guided example code from PDF manuals
- Other skills for document processing and analysis

## Additional Resources

- Reviewer guides: `reviewer/` directory contains reviewer PDFs and Markdown files
- Final review compilation: `output/pdf/Final-Review-All-Modules.pdf`
- Cheat sheets: `reviewer/OpenGL-GLUT-Syntax-Cheatsheet.pdf`

## Build System

The Makefile supports building modules with the following commands:
- `make MODULE=N MODE=examples` - Build example programs
- `make MODULE=N MODE=exercise` - Build exercise programs
- `make MODULE=N MODE=all` - Build both examples and exercises (default)
- `make mNx` - Shortcut for building Module N exercises
- `make mN` - Shortcut for building all of Module N

Builds are written to `build/ModuleN/` directory structure.