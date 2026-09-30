# CS0045 Computer Graphics and Visual Computing

Laboratory work for CS0045 using classic OpenGL and FreeGLUT. Each module contains guided examples, practice exercises, source code, and captured outputs.

## Modules

| Module | Topic | Resources |
| --- | --- | --- |
| 1 | Introduction to Computer Graphics | [Gallery](Module1/README.md) · [Completed manual](Module1/docs/SERRANO_PE_M1.pdf) |
| 2 | OpenGL Primitives and Color | [Gallery](Module2/README.md) · [Completed manual](Module2/docs/SERRANO_PE_M2.pdf) |
| 3 | Text and Event-Driven Interaction | [Gallery](Module3/README.md) · [Completed manual](Module3/docs/SERRANO_PE_M3.pdf) |
| 4 | Vertex Arrays and Indexed Rendering | [Gallery](Module4/README.md) · [Completed manual](Module4/docs/SERRANO_PE_M4.pdf) |

## Run an Activity

From the repository root:

```sh
./run 1e2      # Module 1, guided example 2
./run 1x1      # Module 1, practice exercise 1
./run 4x10     # Module 4, practice exercise 10
```

Use `e` for guided examples and `x` for practice exercises.

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
├── SERRANO_PE_*.cpp  Practice exercise solutions
├── assets/           Tracked PE_* screenshots and GIF demonstrations
└── docs/             Completed manuals
```

Requirements: a C++17 compiler, GNU Make, OpenGL, GLU, and FreeGLUT.
