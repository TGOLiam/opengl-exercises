# Module 4 Reviewer: Vertex Arrays and Indexed Rendering

## Part A — Short MCQ

1. Main advantage of indexed drawing: A. no vertex data B. shared vertices can be reused C. no draw call D. automatic callbacks
2. In `glVertexPointer(3, GL_FLOAT, 0, vertices)`, `3` is: A. vertex count B. coordinate components C. byte stride D. primitive count
3. Which call consumes an index array? A. `glDrawArrays` B. `glVertexPointer` C. `glDrawElements` D. `glColorPointer`

## Part B — Code Tracing

4. How many points are processed?
```cpp
GLfloat v[] = {-1,-1, 0,0, 1,1, .5f,-.5f};
glVertexPointer(2, GL_FLOAT, 0, v);
glDrawArrays(GL_POINTS, 1, 3);
```
   A. 1  B. 2  C. 3  D. 4

5. Which three coordinate pairs are processed in Question 4?  
   A. `(-1,-1),(0,0),(1,1)`  B. `(0,0),(1,1),(.5,-.5)`  C. `(1,1),(.5,-.5),(-1,-1)`  D. `(-1,-1),(1,1),(.5,-.5)`

6. How many triangles are rendered?
```cpp
glDrawArrays(GL_TRIANGLES, 0, 8);
```
   A. 1  B. 2  C. 3  D. 8

7. Find the configuration error.
```cpp
GLfloat vertices[] = {-.5f,-.5f, .5f,-.5f, 0,.5f};
glVertexPointer(3, GL_FLOAT, 0, vertices);
glDrawArrays(GL_TRIANGLES,0,3);
```
   A. `size` should be 2, not 3  B. Type should be `GL_INT`  C. Count should be 6  D. Mode should be `GL_POINTS`

8. Why will this likely ignore the array?
```cpp
glVertexPointer(2, GL_FLOAT, 0, vertices);
glDrawArrays(GL_TRIANGLES,0,3);
```
   A. Color array is missing  B. `GL_VERTEX_ARRAY` was not enabled  C. `glDrawArrays` requires indices  D. Stride cannot be zero

9. Trace the vertex order.
```cpp
GLfloat v[] = {-1,-1,  1,-1,  0,1};
GLubyte i[] = {2,0,1};
glVertexPointer(2,GL_FLOAT,0,v);
glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,i);
```
    A. `(-1,-1) → (1,-1) → (0,1)`  B. `(0,1) → (-1,-1) → (1,-1)`  C. `(1,-1) → (0,1) → (-1,-1)`  D. Indices do not affect order

10. How many unique vertices and processed indices are used?
```cpp
GLfloat v[] = {-1,-1, 1,-1, 1,1, -1,1};
GLubyte i[] = {0,1,2, 0,2,3};
glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_BYTE,i);
```
    A. 6 unique, 4 processed  B. 4 unique, 6 processed  C. 4 unique, 4 processed  D. 6 unique, 6 processed

11. Which vertices form the second triangle in Question 10?  
    A. `0,1,2`  B. `0,2,3`  C. `1,2,3`  D. `3,2,1`

12. What is wrong if Question 10 uses `GL_UNSIGNED_INT` without changing the index array type?  
    A. Nothing  B. The bytes are interpreted using the wrong index size  C. Vertex coordinates become integers  D. It disables indexing

13. What visual effect should this produce?
```cpp
GLfloat colors[] = {1,0,0, 0,1,0, 0,0,1};
glColorPointer(3,GL_FLOAT,0,colors);
glDrawArrays(GL_TRIANGLES,0,3);
```
    A. Solid red triangle  B. Three unconnected points  C. Smooth RGB interpolation, if the color array is enabled  D. Transparent triangle

14. An interleaved vertex contains `x,y,z,r,g,b`. What is its stride in bytes when each value is a four-byte `GLfloat`?  
    A. 6  B. 12  C. 24  D. 36

15. In that layout, how many floats after the record start does color data begin?  
    A. 0  B. 2  C. 3  D. 6

16. Trace both draw calls.
```cpp
glVertexPointer(2,GL_FLOAT,0,v);
glDrawArrays(GL_LINE_LOOP,0,4);
glDrawArrays(GL_POINTS,1,2);
```
    A. A four-vertex loop, then points at vertices 1 and 2  B. Two triangles  C. Four points, then one line  D. Only the loop because arrays cannot be reused

17. Why is this indexed fan more memory-efficient than repeating the center for every triangle?
```cpp
GLubyte idx[] = {0,1,2,3,4,1};
glDrawElements(GL_TRIANGLE_FAN,6,GL_UNSIGNED_BYTE,idx);
```
    A. It stores every center repeatedly  B. The stored center and perimeter vertices are reused by indices  C. Fans never need vertices  D. Indices generate coordinates automatically

18. What happens if `count` refers to more vertices than actually exist in the supplied array?  
    A. OpenGL safely adds zero vertices  B. The draw is automatically shortened  C. Out-of-bounds access causes undefined behavior  D. The compiler always rejects it

## Part C — Fill in the Blanks

19. Complete the basic vertex-array sequence.
```cpp
glEnableClientState(_______________);
glVertexPointer(2, GL_FLOAT, 0, vertices);
____________(GL_TRIANGLES, 0, 3);
glDisableClientState(_______________);
```

20. Complete a vertex plus color array setup.
```cpp
glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(______________);
glVertexPointer(3,GL_FLOAT,0,vertices);
____________(3,GL_FLOAT,0,colors);
```

21. Complete indexed drawing with byte indices.
```cpp
glDrawElements(GL_TRIANGLES, 6, __________________, indices);
```

22. Fill `first` and `count` to draw vertices 3, 4, and 5 as one triangle.
```cpp
glDrawArrays(GL_TRIANGLES, ____, ____);
```

23. A `GLint` array stores x/y pairs. Complete its pointer declaration.
```cpp
glVertexPointer(____, __________, 0, vertices);
```

24. Complete the two client-state shutdown calls.
```cpp
glDisableClientState(______________);
glDisableClientState(_______________);
```

25. Complete pointers for interleaved `x,y,z,r,g,b` data.
```cpp
GLsizei stride = 6 * sizeof(GLfloat);
glVertexPointer(3, GL_FLOAT, stride, data);
glColorPointer(3, GL_FLOAT, stride, data + ____);
```

26. Fill the indices for two triangles forming quad vertices 0–3.
```cpp
GLubyte indices[] = {0,1,2, 0,____,____};
```

27. Use one center and four perimeter vertices to draw a fan with a repeated first perimeter index.
```cpp
GLubyte indices[] = {0,1,2,3,4,____};
glDrawElements(________________, 6, GL_UNSIGNED_BYTE, indices);
```

28. Complete procedural circle positions.
```cpp
for (int i=0; i<=segments; ++i) {
  float a = 2.0f*PI*i/segments;
  vertices[k++] = radius * ______(a);
  vertices[k++] = radius * ______(a);
}
```

29. Complete a keyboard-driven shape switch without rebuilding arrays.
```cpp
if (key>='1' && key<='3') {
    currentShape = key - ____;
    __________________();
}
```

30. Fill the comparison: `glDrawArrays` reads vertices in __________ order, while `glDrawElements` reads them in the order specified by an __________ array.

## Part D — Final Fill-in-the-Blank Review

31. Complete the basic sequence:
```cpp
glEnableClientState(_______________);
glVertexPointer(3,________,0,vertices);
glDrawArrays(____________,0,3);
glDisableClientState(_______________);
```

32. Complete indexed drawing for `GLubyte indices[6]`:
```cpp
glDrawElements(____________,____,__________________,indices);
```

33. Match types: `GLshort` → `________`; `GLushort` → `_________________`; `GLuint` → `_______________`.

34. For interleaved `x,y,z,r,g,b`, complete:
```cpp
GLsizei stride = ____ * sizeof(GLfloat);
glVertexPointer(____,GL_FLOAT,stride,data);
glColorPointer(____,GL_FLOAT,stride,data + ____);
```

35. For interleaved `r,g,b,a,x,y`, color offset is ______ floats and position offset is ______ floats.

36. Complete separate arrays:
```cpp
glEnableClientState(______________);
glColorPointer(3,________,0,colors);
```

37. `glDrawArrays(mode,first,count)` reads vertices in __________ order; `glDrawElements` follows an ________ array.

38. Six floats containing three x/y pairs represent ________ vertices, so the draw count is ________.

39. Complete two triangles sharing four vertices:
```cpp
GLubyte i[] = {0,1,2, 0,____,____};
glDrawElements(GL_TRIANGLES,____,GL_UNSIGNED_BYTE,i);
```

40. Complete client-state cleanup:
```cpp
glDisableClientState(______________);
glDisableClientState(_______________);
```

## Answer Key and Explanations

1. **B**  2. **B**  3. **C**  
4. **C** — `count=3`.  
5. **B** — `first=1` skips the first coordinate pair.  
6. **B** — Two complete triangles; two excess vertices remain.  
7. **A** — The packed array contains x/y pairs, so size must be 2.  
8. **B** — The vertex-array client state was never enabled.  
9. **B** — Indices 2, 0, 1 select top, bottom-left, bottom-right.  
10. **B** — Four stored vertices are referenced six times.  
11. **B** — The second index triplet is 0, 2, 3.  
12. **B** — The declared index type controls how the bytes are interpreted.  
13. **C** — Enabled per-vertex colors interpolate across the triangle.  
14. **C** — Six floats × four bytes = 24 bytes.  
15. **C** — Color starts after x, y, and z.  
16. **A** — The same array supplies a loop and then two selected points.  
17. **B** — Indices reuse stored coordinates rather than duplicating them.  
18. **C** — Reading beyond valid data is undefined behavior.  
19. `GL_VERTEX_ARRAY`; `glDrawArrays`; `GL_VERTEX_ARRAY`  
20. `GL_COLOR_ARRAY`; `glColorPointer`  
21. `GL_UNSIGNED_BYTE`  
22. `3`; `3`  
23. `2`; `GL_INT`  
24. `GL_COLOR_ARRAY`; `GL_VERTEX_ARRAY` (either safe disable order is acceptable)  
25. `3`  
26. `2`; `3`  
27. `1`; `GL_TRIANGLE_FAN`  
28. `cos`; `sin`  
29. `'1'`; `glutPostRedisplay`  
30. **sequential; index**
31. `GL_VERTEX_ARRAY`; `GL_FLOAT`; `GL_TRIANGLES`; `GL_VERTEX_ARRAY`  
32. `GL_TRIANGLES`; `6`; `GL_UNSIGNED_BYTE`  
33. `GL_SHORT`; `GL_UNSIGNED_SHORT`; `GL_UNSIGNED_INT`  
34. `6`; `3`; `3`; `3`  
35. `0`; `4`  
36. `GL_COLOR_ARRAY`; `GL_FLOAT`  
37. **sequential; index**  
38. `3`; `3`  
39. `2`; `3`; `6`  
40. `GL_COLOR_ARRAY`; `GL_VERTEX_ARRAY`
