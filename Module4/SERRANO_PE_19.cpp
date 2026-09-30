#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Each vertex stores x, y, z, r, g, b: 6 floats per vertex.
GLfloat hexagon[] = {
   0.0f,  0.65f, 0.0f,  1.0f, 0.2f, 0.2f,
   0.56f, 0.32f, 0.0f,  1.0f, 0.7f, 0.1f,
   0.56f, -0.32f, 0.0f,  0.2f, 0.8f, 0.2f,
   0.0f, -0.65f, 0.0f,  0.1f, 0.7f, 1.0f,
  -0.56f, -0.32f, 0.0f,  0.3f, 0.2f, 1.0f,
  -0.56f,  0.32f, 0.0f,  0.9f, 0.2f, 0.8f,
};

GLubyte indices[] = {0, 1, 2, 3, 4, 5};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLsizei stride = 6 * sizeof(GLfloat);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, stride, hexagon);
  glColorPointer(3, GL_FLOAT, stride, hexagon + 3);
  glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, indices);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_19 - Interleaved Indexed Hexagon");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
