#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat data[] = {
  // x,      y,      z,       r,    g,    b
  -0.6f,  -0.4f,   0.0f,     1.0f, 0.0f, 0.0f,
   0.6f,  -0.4f,   0.0f,     0.0f, 1.0f, 0.0f,
   0.6f,   0.4f,   0.0f,     0.0f, 0.0f, 1.0f,
  -0.6f,   0.4f,   0.0f,     1.0f, 1.0f, 0.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLsizei stride = 6 * sizeof(GLfloat);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, stride, data);
  glColorPointer(3, GL_FLOAT, stride, data + 3);
  glDrawArrays(GL_QUADS, 0, 4);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_12 - Interleaved Array Quad");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
