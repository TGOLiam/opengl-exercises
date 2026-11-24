# OpenGL and GLUT Syntax Cheatsheet

This sheet covers the OpenGL and GLUT/freeGLUT names used in `Module1/example` through `Module4/example`.

## 1. Headers and namespaces

```cpp
#include <GL/glut.h>          // OpenGL + GLUT on Windows/Linux
#include <GL/freeglut_ext.h>  // freeGLUT extension functions
#include <GLUT/glut.h>        // GLUT header used on macOS

#include <iostream>           // cout, endl
#include <cmath>              // sin, cos
#include <cstdio>             // sprintf
#include <chrono>             // time measurements

using namespace std;
```

`GL` and `GLUT` are **prefixes**, not C++ namespaces. OpenGL names begin with `gl` or `GL_`; GLUT names begin with `glut` or `GLUT_`. `std` is the C++ standard-library namespace.

Common OpenGL types:

| Type | Meaning |
|---|---|
| `GLfloat` | OpenGL floating-point value |
| `GLshort` | Signed short integer |
| `GLubyte` | Unsigned byte, often used for colors or indices |
| `GLsizei` | Non-negative size/count type |
| `GLenum` | Named OpenGL constant such as `GL_TRIANGLES` |

---

## 2. Minimal GLUT program

```cpp
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing commands

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Title");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

## 3. GLUT initialization and window functions

### `glutInit`

```cpp
void glutInit(int* argc, char** argv);
glutInit(&argc, argv);
```

Initializes GLUT. Call it before other GLUT functions.

### `glutInitWindowSize`

```cpp
void glutInitWindowSize(int width, int height);
glutInitWindowSize(800, 600);
```

Sets the initial window size in pixels.

### `glutInitWindowPosition`

```cpp
void glutInitWindowPosition(int x, int y);
glutInitWindowPosition(100, 50);
```

Sets the initial screen position of the window's upper-left corner.

### `glutCreateWindow`

```cpp
int glutCreateWindow(const char* title);
glutCreateWindow("Computer Graphics");
```

Creates a window and OpenGL context. The return value is a window identifier.

### `glutFullScreen`

```cpp
void glutFullScreen(void);
glutFullScreen();
```

Requests fullscreen mode for the current window.

### `glutReshapeWindow`

```cpp
void glutReshapeWindow(int width, int height);
glutReshapeWindow(600, 400);
```

Changes the current window's size.

### `glutGet`

```cpp
int glutGet(GLenum query);

int width  = glutGet(GLUT_WINDOW_WIDTH);
int height = glutGet(GLUT_WINDOW_HEIGHT);
```

Queries GLUT state. Examples use:

- `GLUT_WINDOW_WIDTH`
- `GLUT_WINDOW_HEIGHT`

### `glutMainLoop`

```cpp
void glutMainLoop(void);
glutMainLoop();
```

Starts the event loop. It is normally the final GLUT call in `main()`.

### `glutPostRedisplay`

```cpp
void glutPostRedisplay(void);
glutPostRedisplay();
```

Marks the current window for redrawing. GLUT later invokes the registered display callback.

---

## 4. GLUT callback registration

Registration functions receive a **function name without parentheses**.

### Display callback

```cpp
void display(void);
glutDisplayFunc(display);
```

```cpp
void glutDisplayFunc(void (*func)(void));
```

### Keyboard callback

```cpp
void keyboard(unsigned char key, int x, int y);
glutKeyboardFunc(keyboard);
```

```cpp
void glutKeyboardFunc(void (*func)(unsigned char, int, int));
```

- `key`: pressed ASCII key
- `x`, `y`: mouse position when the key was pressed

### Mouse-button callback

```cpp
void mouse(int button, int state, int x, int y);
glutMouseFunc(mouse);
```

```cpp
void glutMouseFunc(void (*func)(int, int, int, int));
```

Button values:

- `GLUT_LEFT_BUTTON`
- `GLUT_MIDDLE_BUTTON`
- `GLUT_RIGHT_BUTTON`

State values:

- `GLUT_DOWN`
- `GLUT_UP`

Example:

```cpp
if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    // Left button pressed
}
```

### Active mouse-motion callback

```cpp
void drag(int x, int y);
glutMotionFunc(drag);
```

Runs when the pointer moves while a mouse button is pressed.

### Passive mouse-motion callback

```cpp
void hover(int x, int y);
glutPassiveMotionFunc(hover);
```

Runs when the pointer moves with no mouse button pressed.

### Mouse entry/exit callback

```cpp
void entry(int state);
glutEntryFunc(entry);
```

`state` is:

- `GLUT_ENTERED`
- `GLUT_LEFT`

### Idle callback

```cpp
void animate(void);
glutIdleFunc(animate);
```

Runs when GLUT has no other event to process. Calling `glutIdleFunc(nullptr)` removes the callback.

### Timer callback

```cpp
void timer(int value);
glutTimerFunc(1000, timer, 0);
```

```cpp
void glutTimerFunc(unsigned int milliseconds,
                   void (*func)(int),
                   int value);
```

A timer executes **once**. Reschedule it inside the callback to repeat:

```cpp
void timer(int value) {
    // Update state
    glutPostRedisplay();
    glutTimerFunc(1000, timer, value);
}
```

---

## 5. Clearing and command execution

### `glClearColor`

```cpp
void glClearColor(GLfloat red, GLfloat green,
                  GLfloat blue, GLfloat alpha);

glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
```

Sets the color used by a later color-buffer clear. Components normally range from `0.0f` to `1.0f`.

### `glClear`

```cpp
void glClear(GLbitfield mask);
glClear(GL_COLOR_BUFFER_BIT);
```

Clears the selected buffers. Call it before drawing a new frame.

### `glFlush`

```cpp
void glFlush(void);
glFlush();
```

Forces previously issued OpenGL commands to begin execution.

---

## 6. Immediate-mode drawing

### `glBegin` and `glEnd`

```cpp
void glBegin(GLenum mode);
void glEnd(void);

glBegin(GL_TRIANGLES);
// vertices and per-vertex attributes
glEnd();
```

Primitive modes used in the examples:

| Mode | Vertex interpretation |
|---|---|
| `GL_POINTS` | One point per vertex |
| `GL_LINES` | One independent line per pair |
| `GL_LINE_STRIP` | Connected open sequence |
| `GL_LINE_LOOP` | Connected sequence plus closing edge |
| `GL_TRIANGLES` | One independent triangle per group of 3 |
| `GL_TRIANGLE_STRIP` | Connected triangles; each new vertex adds one |
| `GL_TRIANGLE_FAN` | Triangles sharing the first vertex |
| `GL_QUADS` | One independent quadrilateral per group of 4 |
| `GL_QUAD_STRIP` | Connected quadrilaterals from vertex pairs |
| `GL_POLYGON` | One filled convex polygon |

### `glVertex2f`

```cpp
void glVertex2f(GLfloat x, GLfloat y);
glVertex2f(-0.5f, 0.5f);
```

Submits one 2D vertex. With the default setup, visible x/y coordinates are generally between `-1` and `1`.

---

## 7. Colors and shading

### `glColor3f`

```cpp
void glColor3f(GLfloat red, GLfloat green, GLfloat blue);
glColor3f(1.0f, 0.0f, 0.0f); // red
```

Uses floating-point RGB components from `0.0f` to `1.0f`.

### `glColor3ub`

```cpp
void glColor3ub(GLubyte red, GLubyte green, GLubyte blue);
glColor3ub(255, 128, 0); // orange
```

Uses unsigned-byte RGB components from `0` to `255`.

### `glColor4f`

```cpp
void glColor4f(GLfloat red, GLfloat green,
               GLfloat blue, GLfloat alpha);
glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
```

Adds alpha. `1.0f` is opaque; `0.0f` is transparent. Blending must also be enabled for normal transparency.

### `glShadeModel`

```cpp
void glShadeModel(GLenum mode);
glShadeModel(GL_SMOOTH);
```

`GL_SMOOTH` interpolates per-vertex colors across a primitive.

---

## 8. Point, line, stipple, and blending state

### `glPointSize`

```cpp
void glPointSize(GLfloat size);
glPointSize(10.0f);
```

Sets point size in pixels.

### `glLineWidth`

```cpp
void glLineWidth(GLfloat width);
glLineWidth(3.0f);
```

Sets line width.

### `glEnable` and `glDisable`

```cpp
void glEnable(GLenum capability);
void glDisable(GLenum capability);

glEnable(GL_LINE_STIPPLE);
// draw stippled lines
glDisable(GL_LINE_STIPPLE);
```

Capabilities used:

- `GL_LINE_STIPPLE`
- `GL_BLEND`

### `glLineStipple`

```cpp
void glLineStipple(GLint factor, GLushort pattern);
glLineStipple(2, 0xAAAA);
```

- `factor`: how many times each bit is repeated
- `pattern`: repeating 16-bit on/off mask

The feature must first be enabled with `glEnable(GL_LINE_STIPPLE)`.

### `glBlendFunc`

```cpp
void glBlendFunc(GLenum sourceFactor, GLenum destinationFactor);

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

This common configuration combines the incoming color using its alpha with the existing framebuffer color.

---

## 9. Bitmap and stroke text

### `glRasterPos2f`

```cpp
void glRasterPos2f(GLfloat x, GLfloat y);
glColor3f(1, 1, 1);
glRasterPos2f(-0.5f, 0.0f);
```

Sets the starting raster position for bitmap text. In the course examples, set color before setting the raster position.

### `glutBitmapCharacter`

```cpp
void glutBitmapCharacter(void* font, int character);
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
```

Portable string helper:

```cpp
void drawBitmapString(void* font, const char* text) {
    for (const char* c = text; *c != '\0'; ++c)
        glutBitmapCharacter(font, *c);
}
```

### `glutBitmapString`

```cpp
void glutBitmapString(void* font, const unsigned char* text);

glutBitmapString(GLUT_BITMAP_HELVETICA_18,
                 (const unsigned char*)"Hello");
```

This is a freeGLUT extension and may require `<GL/freeglut_ext.h>`. It is not present in every GLUT implementation.

Bitmap fonts used:

- `GLUT_BITMAP_9_BY_15`
- `GLUT_BITMAP_HELVETICA_10`
- `GLUT_BITMAP_HELVETICA_12`
- `GLUT_BITMAP_HELVETICA_18`
- `GLUT_BITMAP_TIMES_ROMAN_10`
- `GLUT_BITMAP_TIMES_ROMAN_24`

### `glutStrokeCharacter`

```cpp
void glutStrokeCharacter(void* font, int character);
glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A');
```

Stroke text is vector-based and can be translated or scaled.

---

## 10. Matrix transformations used with stroke text

### `glPushMatrix` and `glPopMatrix`

```cpp
glPushMatrix();
// temporary transformations and drawing
glPopMatrix();
```

They save and restore the current matrix so transformations do not affect later objects.

### `glTranslatef`

```cpp
void glTranslatef(GLfloat x, GLfloat y, GLfloat z);
glTranslatef(-0.5f, 0.0f, 0.0f);
```

Moves subsequent geometry.

### `glScalef`

```cpp
void glScalef(GLfloat x, GLfloat y, GLfloat z);
glScalef(0.002f, 0.002f, 1.0f);
```

Scales subsequent geometry. It is useful because GLUT stroke fonts use large coordinate units.

Typical stroke-text pattern:

```cpp
glPushMatrix();
glTranslatef(-0.5f, 0.0f, 0.0f);
glScalef(0.002f, 0.002f, 1.0f);

for (const char* c = "HELLO"; *c; ++c)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);

glPopMatrix();
```

---

## 11. Vertex arrays

### Standard vertex-array sequence

```cpp
glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3, GL_FLOAT, 0, vertices);
glDrawArrays(GL_TRIANGLES, 0, 3);
glDisableClientState(GL_VERTEX_ARRAY);
```

### `glEnableClientState` and `glDisableClientState`

```cpp
void glEnableClientState(GLenum array);
void glDisableClientState(GLenum array);
```

Arrays used:

- `GL_VERTEX_ARRAY`
- `GL_COLOR_ARRAY`

These are distinct from `glEnable` and `glDisable`.

### `glVertexPointer`

```cpp
void glVertexPointer(GLint size, GLenum type,
                     GLsizei stride, const void* pointer);

glVertexPointer(3, GL_FLOAT, 0, vertices);
```

- `size`: components per vertex, usually 2 or 3
- `type`: stored component type, such as `GL_FLOAT` or `GL_SHORT`
- `stride`: byte distance between consecutive positions; `0` means tightly packed
- `pointer`: first position value

### `glColorPointer`

```cpp
void glColorPointer(GLint size, GLenum type,
                    GLsizei stride, const void* pointer);

glColorPointer(3, GL_FLOAT, 0, colors);
```

Describes an array of per-vertex colors. Enable `GL_COLOR_ARRAY` before drawing.

### `glDrawArrays`

```cpp
void glDrawArrays(GLenum mode, GLint first, GLsizei count);
glDrawArrays(GL_TRIANGLES, 0, 6);
```

- `mode`: primitive interpretation
- `first`: index of the first sequential vertex
- `count`: number of vertices to process, not number of primitives

### `glDrawElements`

```cpp
void glDrawElements(GLenum mode, GLsizei count,
                    GLenum indexType, const void* indices);

glDrawElements(GL_TRIANGLES, 6,
               GL_UNSIGNED_BYTE, indices);
```

- `count`: number of indices to read
- `indexType`: type stored in the index array
- `indices`: index-array address

Types used in the examples:

- `GL_UNSIGNED_BYTE` for `GLubyte` indices
- `GL_FLOAT` for `GLfloat` attributes
- `GL_SHORT` for `GLshort` attributes

### Interleaved vertex and color data

```cpp
GLfloat data[] = {
    // x, y, z,   r, g, b
     0, 1, 0,     1, 0, 0,
    -1,-1, 0,     0, 1, 0,
     1,-1, 0,     0, 0, 1
};

GLsizei stride = 6 * sizeof(GLfloat);

glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);

glVertexPointer(3, GL_FLOAT, stride, data);
glColorPointer(3, GL_FLOAT, stride, data + 3);
glDrawArrays(GL_TRIANGLES, 0, 3);

glDisableClientState(GL_COLOR_ARRAY);
glDisableClientState(GL_VERTEX_ARRAY);
```

`stride` is the size of one complete record. `data + 3` is the color offset after x, y, and z.

---

## 12. Quick callback reference

| Registration | Required callback signature | Trigger |
|---|---|---|
| `glutDisplayFunc(display)` | `void display()` | Window must be drawn |
| `glutKeyboardFunc(keyboard)` | `void keyboard(unsigned char,int,int)` | Normal key press |
| `glutMouseFunc(mouse)` | `void mouse(int,int,int,int)` | Mouse press/release |
| `glutMotionFunc(motion)` | `void motion(int,int)` | Move with button held |
| `glutPassiveMotionFunc(motion)` | `void motion(int,int)` | Move with no button held |
| `glutEntryFunc(entry)` | `void entry(int)` | Pointer enters/leaves |
| `glutIdleFunc(idle)` | `void idle()` | No pending event |
| `glutTimerFunc(ms,timer,value)` | `void timer(int)` | One timer expires |

## 13. Common syntax traps

1. Register callbacks without parentheses:

   ```cpp
   glutDisplayFunc(display);   // correct
   // glutDisplayFunc(display()); // wrong
   ```

2. Clear before drawing:

   ```cpp
   glClear(GL_COLOR_BUFFER_BIT);
   // draw
   glFlush();
   ```

3. Keep `glBegin` and `glEnd` paired.
4. `glDrawArrays(..., count)` counts vertices; `glDrawElements(..., count, ...)` counts indices.
5. Enable `GL_VERTEX_ARRAY` and `GL_COLOR_ARRAY` before using their pointers.
6. Match pointer/index types to the actual C++ array types.
7. `glutTimerFunc` fires once unless the callback schedules another timer.
8. Updating a variable does not automatically redraw; call `glutPostRedisplay()`.
9. Alpha does not create normal transparency by itself; enable blending and set `glBlendFunc`.
10. In interleaved arrays, stride is measured in **bytes**, not floats.

## 14. Naming pattern memory aid

```text
glVertex2f
│  │     └─ f = float
│  └─────── 2 = two components (x, y)
└────────── gl = OpenGL function

GL_TRIANGLES
└─ OpenGL constant

glutKeyboardFunc
└─ GLUT function

GLUT_LEFT_BUTTON
└─ GLUT constant
```
