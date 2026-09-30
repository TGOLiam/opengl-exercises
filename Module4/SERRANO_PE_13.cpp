#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat pinwheelVertices[] = {
   0.0f,  0.0f,  0.0f,  // 0: shared center
  -0.5f,  0.1f,  0.0f,  // 1: left-top
  -0.5f, -0.1f,  0.0f,  // 2: left-bottom
   0.5f,  0.1f,  0.0f,  // 3: right-top
   0.5f, -0.1f,  0.0f,  // 4: right-bottom
  -0.1f,  0.5f,  0.0f,  // 5: top-left
   0.1f,  0.5f,  0.0f,  // 6: top-right
  -0.1f, -0.5f,  0.0f,  // 7: bottom-left
   0.1f, -0.5f,  0.0f,  // 8: bottom-right
};

GLfloat pinwheelColors[] = {
  1.0f, 1.0f, 1.0f,
  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,
  1.0f, 0.5f, 0.0f,  0.5f, 0.0f, 1.0f,
};

GLubyte pinwheelIndices[] = {
  0, 1, 2,
  0, 3, 4,
  0, 5, 6,
  0, 7, 8,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, pinwheelVertices);
  glColorPointer(3, GL_FLOAT, 0, pinwheelColors);
  glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, pinwheelIndices);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_13 - Indexed Pinwheel");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
