# CS0045 Computer Graphics and Visual Computing

This repository contains the laboratory work for **CS0045 Computer Graphics and Visual Computing**. The exercises begin with the basic OpenGL drawing pipeline, then gradually introduce procedural geometry, color, keyboard interaction, and animation through small programs that can be studied one concept at a time.

The code uses classic OpenGL with FreeGLUT so the early graphics concepts remain visible: creating a window, clearing the framebuffer, submitting vertices, choosing primitive types, and responding to events.

<p align="center"><img src="Module1/assets/outputs/PE_14.png" alt="Module 1 OpenGL landscape exercise with a blue sky, green ground, and yellow sun" width="640"></p>

## Module 1 Introduction to Computer Graphics

Module 1 moves from a single point and line to compound scenes and interactive programs. It includes 20 guided examples, 20 mini-exercises, and 20 practice exercises.

The module focuses on:

- setting up an OpenGL and FreeGLUT window;
- drawing points, lines, triangles, and polygons;
- working with coordinates, colors, and smooth shading;
- generating shapes with loops and trigonometry;
- handling keyboard input; and
- creating simple frame-based animation.

Open the [Module 1 exercise gallery](Module1/README.md) to view every practice question alongside its captured output, including GIF demonstrations for animated and keyboard-controlled programs.

## Working Through the Laboratory

1. Run the guided example for the topic and observe its output.
2. Read the source and identify the OpenGL calls responsible for the result.
3. Attempt the related mini-exercise as a short concept check.
4. Complete the practice exercise without copying the answer directly.
5. Compare the program window with the output shown in the exercise gallery.

The course materials are available here:

- [Module 1 student laboratory manual](Module1/docs/Module_01_Student_Laboratory_Manual.docx)
- [Module 1 manual with exercise outputs](Module1/docs/Module_01_Student_Laboratory_Manual_with_outputs.docx)
- [Module 1 practice exercises and outputs](Module1/README.md)

## Running a Course Activity

From the repository root, use `./run` with the module number, activity type, and activity number:

```sh
./run 1 e 2    # guided example 2
./run 1 m 3    # mini-exercise 3
./run 1 x 1    # practice exercise 1
```

The activity types are `e` for guided examples, `m` for mini-exercises, and `x` for practice exercises. The command compiles the selected program and opens its GLUT window.

To compile a complete group without immediately opening each program:

```sh
make m1     # all Module 1 activities
make m1e    # guided examples
make m1x    # practice exercises
```

Use `make help` for the full command list. Compiled programs are placed in `build/Module1/`.

## Course Folder Guide

- `Module1/example/` contains the guided programs discussed in the manual.
- `Module1/mini-exercises/` contains shorter concept checks.
- `Module1/SERRANO_PE_01.cpp` through `SERRANO_PE_20.cpp` contain the practice exercise solutions.
- `Module1/assets/outputs/` contains the screenshots and GIF demonstrations used by the gallery.
- `Module1/docs/` contains the laboratory manual and completed document copy.

The local toolchain requires a C++ compiler, GNU Make, OpenGL, GLU, and FreeGLUT. The provided build setup uses `g++` with C++17.
