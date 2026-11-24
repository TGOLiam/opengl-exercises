# Repository guidance

This repository contains CS0045 OpenGL laboratory work. Follow the relevant module manual and nearby exercises when implementing a task; the conventions below describe the existing work, not a substitute for the exercise requirements.

## Typical module workflow

Module tasks commonly begin with a student laboratory PDF, continue with standalone practice exercise solutions, and end with a supplied Word manual and a gallery documenting the outputs. Use these repository-local skills when the corresponding work is requested:

- **Guided examples:** Read `.agents/skills/opengl-pdf-example-extractor/SKILL.md` to extract and verify the Part A examples from the module PDF into `ModuleN/example/`. Preserve the manual's example code apart from extraction repairs.
- **Module documentation:** Read `.agents/skills/opengl-module-documentation/SKILL.md` to prepare numbered output media, embed the outputs in the given Word manual, generate the gallery, and visually verify the completed document. When capture is requested, automate screenshots for static exercises and record animations or interactions so the required behavior is visible.

Apply each skill to its own stage and follow its detailed instructions. Preserve the supplied source manual and keep exercise numbers matched across code, media, gallery, and documentation.

## Project structure

- Put practice exercises in `ModuleN/SERRANO_PE_NN.cpp`, with two-digit exercise numbers. Each exercise is a standalone program with its own `main`.
- Keep guided examples in `ModuleN/example/`, module documentation in `ModuleN/docs/`, and output media in `ModuleN/assets/`. Module READMEs provide exercise galleries and links to their sources.
- Use the existing root Makefile and `./run` launcher. Build practice exercises with `make MODULE=N MODE=exercise` or `make mNx`; build outputs go under `build/ModuleN/`.

## C++ and OpenGL patterns

- When assigning or delegating implementation, instruct contributors to inspect the user's existing exercises and follow these code patterns and the relevant module's style. Review delegated work for consistency with those patterns and the manual's requirements.
- Keep solutions direct and self-contained, using the OpenGL and GLUT techniques taught in the corresponding module. Prefer small functions and straightforward arrays over a shared framework or unrelated abstractions.
- Follow the nearby module's formatting and naming. Recent exercises generally use two-space indentation, descriptive camelCase helper and callback names, and `PE_NN - description` window titles.
- Define `GL_SILENCE_DEPRECATION`, use the existing Apple/other platform include guards, and include GLEW before GLUT on non-Apple platforms when buffer or extension functions require it. Initialize GLEW after creating the window when it is needed.
- Put rendering in a `display` callback and set up GLUT in `main`: initialize GLUT, create a typically 600-by-600 window, register the callbacks, and enter `glutMainLoop()`. Match the exercise's display mode, depth handling, and buffer flushing or swapping requirements.
- Use GLUT keyboard, mouse, and timer callbacks for interactive or animated exercises as appropriate. Keep state and small helper functions local to the standalone exercise, and release OpenGL resources when their lifetime requires it.
- Preserve the lesson's intended approach: earlier work uses immediate mode, later work introduces vertex arrays, VBOs, and explicit matrix operations. Do not replace a requested teaching technique with a different rendering architecture.

## Documentation and verification

- Preserve the original laboratory manual. For module documentation, follow the repository's `opengl-module-documentation` skill when applicable, including numbered media mapping, gallery generation, and rendered manual inspection.
- Use still captures for static output and recordings that show the actual behavior for animated or interactive exercises. Do not substitute another exercise's output.
- Compile the affected exercises and perform checks appropriate to the change. Avoid changing unrelated modules or overwriting existing user files.
