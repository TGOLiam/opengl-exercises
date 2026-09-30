#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat triangle[] = {
   0.0f,  0.7f,
  -0.7f, -0.6f,
   0.7f, -0.6f,
};

GLfloat colors[] = {
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(2, GL_FLOAT, 0, triangle);
  glColorPointer(3, GL_FLOAT, 0, colors);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_07 - Vertex and Color Arrays");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
