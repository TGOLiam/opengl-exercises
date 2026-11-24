# VBO and Matrix Cheatsheet

This sheet collects the VBO, vertex/color array, and transformation-matrix syntax used in the Module 5 and Module 6 examples. The code follows the project's legacy OpenGL style with GLEW, GLUT, and client-state arrays.

## VBO flow

```cpp
GLfloat vertices[] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

GLuint vbo;
glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3, GL_FLOAT, 0, nullptr);
glDrawArrays(GL_TRIANGLES, 0, 3);
glDisableClientState(GL_VERTEX_ARRAY);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &vbo);
```

| Call | Argument meaning |
|---|---|
| `glGenBuffers(1, &vbo)` | Generate 1 buffer name and write it into `vbo`. |
| `glBindBuffer(GL_ARRAY_BUFFER, vbo)` | Bind this buffer as the source for vertex attributes. |
| `glBufferData(target, size, data, usage)` | Allocate `size` bytes; optionally copy `data`; provide a usage hint. |
| `glEnableClientState(GL_VERTEX_ARRAY)` | Enable the position array. |
| `glVertexPointer(3, GL_FLOAT, 0, nullptr)` | Read 3 floats per vertex, tightly packed, from byte offset 0. |
| `glDrawArrays(mode, first, count)` | Draw `count` vertices starting at vertex index `first`. |
| `glBindBuffer(target, 0)` | Unbind from that target. This does not delete the buffer. |
| `glDeleteBuffers(1, &vbo)` | Delete 1 buffer object. |

Common usage hints: `GL_STATIC_DRAW` for data updated rarely and drawn many times; `GL_DYNAMIC_DRAW` for data updated repeatedly and drawn many times; `GL_STREAM_DRAW` for data updated once and drawn only a few times. They are hints about intended use.

## Counts, sizes, and offsets

- `glBufferData` and `glBufferSubData` sizes and offsets are **bytes**.
- `glVertexPointer` and `glColorPointer` stride and pointer/offset arguments are **bytes**.
- `glDrawArrays` count is **vertices**; `glDrawElements` count is **indices**.
- An XYZ vertex has 3 floats. In a packed `GLfloat` array, vertex `n` starts at float index `3*n`.
- Example: 18 floats of XYZ data = 6 vertices, so draw count is 6, not 18.
- Prefer `sizeof(array)` when the variable is an actual C++ array. `sizeof(pointer)` is only the pointer size, not the pointed-to data size.

With a VBO bound, pointer values such as `nullptr` or `(void*)offsetBytes` are offsets into that VBO, not CPU addresses.

## Indexed drawing with an EBO

An element/ index buffer stores indices that select and reuse vertices:

```cpp
GLubyte indices[] = {0, 1, 2, 0, 2, 3};
GLuint ebo;
glGenBuffers(1, &ebo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
```

The index type must match the array: `GLubyte` → `GL_UNSIGNED_BYTE`, `GLushort` → `GL_UNSIGNED_SHORT`, `GLuint` → `GL_UNSIGNED_INT`. The draw count is the number of indices. Indices are not normals; an index buffer does not require `GL_NORMAL_ARRAY`.

## Color arrays and buffer layouts

Each RGB color has 3 values. OpenGL pairs attribute entry `i` with vertex `i`.

**One VBO with position block followed by color block:**

```cpp
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER,
             sizeof(vertices) + sizeof(colors), nullptr, GL_STATIC_DRAW);
glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);
glVertexPointer(3, GL_FLOAT, 0, nullptr);
glColorPointer(3, GL_FLOAT, 0, (void*)sizeof(vertices));
glDrawArrays(GL_TRIANGLES, 0, 3);
```

`glBufferSubData(target, byteOffset, byteSize, source)` copies source bytes into an already allocated region. Allocate enough storage first. A safer offset style is:

```cpp
#define BUFFER_OFFSET(i) ((void*)(i))
glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(sizeof(vertices)));
```

Other possible layout: interleaved data such as `xyz rgb xyz rgb ...`. Then stride is bytes between vertex starts, and each attribute pointer gets its byte offset within one vertex. See `Module5/example/12.cpp`.

## Matrix and homogeneous-coordinate conventions

The manual matrix examples use a flat, **row-major** array and multiply a column vector: `result = M * v`.

```cpp
M[row * 4 + column] // flat-array index for matrix cell (row, column)
```

Represent a position as `(x, y, z, 1)` and a direction as `(x, y, z, 0)`. `w=0` makes the translation part contribute zero; rotation and scaling can still change a direction. Ordinary model vertices in these examples are positions, so use `w=1`.

## 4x4 matrix times 4x1 vector

Every output is one row of the matrix dotted with the input vector:

```cpp
void multiply4x4Vector(const float M[16], const float v[4], float out[4]) {
    for (int row = 0; row < 4; ++row) {
        out[row] = 0.0f;
        for (int col = 0; col < 4; ++col) {
            out[row] += M[row * 4 + col] * v[col];
        }
    }
}
```

Direct form:

```cpp
out[0] = M[0]*v[0]  + M[1]*v[1]  + M[2]*v[2]  + M[3]*v[3];
out[1] = M[4]*v[0]  + M[5]*v[1]  + M[6]*v[2]  + M[7]*v[3];
out[2] = M[8]*v[0]  + M[9]*v[1]  + M[10]*v[2] + M[11]*v[3];
out[3] = M[12]*v[0] + M[13]*v[1] + M[14]*v[2] + M[15]*v[3];
```

The examples that update 3D VBO coordinates often calculate only `out[0..2]`, because their affine T/R/S transforms preserve `w`; they do not show the whole 4x1 result. Example 9 calculates all four components.

## 4x4 matrix times 4x4 matrix

`C = A * B`; each output cell is a row of `A` dotted with a column of `B`:

```cpp
void multiply4x4(const float A[16], const float B[16], float C[16]) {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            C[row * 4 + col] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                C[row * 4 + col] +=
                    A[row * 4 + k] * B[k * 4 + col];
            }
        }
    }
}
```

Direct expansion of the first cell:

```cpp
C[0] = A[0]*B[0] + A[1]*B[4] + A[2]*B[8] + A[3]*B[12];
```

The loop computes all 16 cells; direct code spells the same pattern out 16 times. Use a separate output array, because this loop overwrites `C` as it goes. If output must replace an input, calculate into a temporary array first.

## Transformation matrices

Let `c = cos(angle)` and `s = sin(angle)`. The trig angle must be in radians; convert degrees with `radians = degrees * pi / 180`.

```text
Translation T(tx,ty,tz):
[1  0  0  tx]
[0  1  0  ty]
[0  0  1  tz]
[0  0  0   1]

Scale S(sx,sy,sz):
[sx  0   0  0]
[0   sy  0  0]
[0   0   sz 0]
[0   0   0  1]

Rotate X:
[1  0   0  0]
[0  c  -s  0]
[0  s   c  0]
[0  0   0  1]

Rotate Y:
[ c  0  s  0]
[ 0  1  0  0]
[-s  0  c  0]
[ 0  0  0  1]

Rotate Z:
[c  -s  0  0]
[s   c  0  0]
[0   0  1  0]
[0   0  0  1]
```

For a rotation, the axis coordinate stays fixed: X rotation mixes Y/Z; Y rotation mixes X/Z; Z rotation mixes X/Y. With the usual XY drawing orientation (+X right, +Y up), positive Z angles rotate counterclockwise and negative angles clockwise.

The examples’ transform helpers often use a direct formula rather than a general matrix-vector function:

```cpp
// Translation, position w=1
newX = x + tx; newY = y + ty; newZ = z + tz;

// Scale
newX = sx*x; newY = sy*y; newZ = sz*z;

// Rotate around Z
newX = c*x - s*y;
newY = s*x + c*y;
newZ = z;
```

These are simplified forms of multiplying the corresponding matrix by `(x,y,z,1)`.

## Transform every vertex in a mapped VBO

Packed XYZ vertices start at float indices `0, 3, 6, ...`:

```cpp
glBindBuffer(GL_ARRAY_BUFFER, vbo);
GLfloat* p = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
if (p != nullptr) {
    for (int i = 0; i < floatCount; i += 3) {
        float x = p[i];
        float y = p[i + 1];
        float z = p[i + 2];

        // Compute all new coordinates from original x,y,z first.
        p[i]     = /* newX */;
        p[i + 1] = /* newY */;
        p[i + 2] = /* newZ */;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
}
```

Map the intended buffer first, check the returned pointer, compute results before overwriting coordinates, then unmap before drawing. `glMapBuffer` can wait for GPU work to finish. If the VBO stores positions and colors in separate blocks, transform only the position block.

## Animation callback pattern

```cpp
void update(int value) {
    // Bind, map, change coordinates, unmap.
    glutPostRedisplay();
    glutTimerFunc(1000, update, value + 1);
}
```

`glutTimerFunc` schedules a one-shot callback after the delay in milliseconds; reschedule it inside the callback for repetition. `glutPostRedisplay` asks GLUT to call the display function again. Avoid starting a new repeating timer every time the display callback runs.

Repeatedly transforming the already changed coordinates accumulates the change. For example, applying a 1.5 scale every update grows by another factor of 1.5 each time. To animate from a fixed base shape, keep original coordinates and recompute from them each frame.

## Combining transforms and order

For column vectors, `v' = T * R * S * v` applies **S first, then R, then T**. Matrix multiplication is associative, so compute a combined matrix once:

```cpp
multiply4x4(T, S, TS); // TS = T*S
out = TS * v;
```

Order matters: generally `T*S` differs from `S*T`. Example 14 multiplies T and S with loops, then directly calculates the first three components of the resulting matrix times one position vector.

## Fixed-function matrix calls in the practicals

Some practical files use OpenGL’s matrix state rather than editing VBO coordinates:

```cpp
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(tx, ty, tz);
glRotatef(degrees, axisX, axisY, axisZ);
glScalef(sx, sy, sz);
```

`glRotatef` takes degrees. These calls transform rendering through OpenGL’s current matrix state; the Module 6 helper examples instead map and change the stored vertex coordinates. Do not pass the examples’ row-major arrays directly to `glLoadMatrixf` without accounting for OpenGL’s matrix storage convention.

## Examples to revisit

- `Module5/example/2.cpp`: basic VBO creation and drawing.
- `Module5/example/9.cpp` and `10.cpp`: indexed drawing.
- `Module5/example/11.cpp` and `12.cpp`: color arrays and layouts.
- `Module6/example/3.cpp` and `4.cpp`: shapes stored in VBOs.
- `Module6/example/5.cpp` and `6.cpp`: one-time and repeated translation.
- `Module6/example/7.cpp` and `8.cpp`: scaling and Z rotation.
- `Module6/example/9.cpp` and `10.cpp`: matrix-vector product and homogeneous coordinates.
- `Module6/example/14.cpp`: 4x4 matrix multiplication and combined transform.
- `Module6/example/19.cpp` and `20.cpp`: transform position data while color data shares the VBO.
- `Module6/example/21.cpp` to `23.cpp`: visual rotation and position/direction demonstrations.
