#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat square[] = {
  -0.5f, -0.5f,
   0.5f, -0.5f,
   0.5f,  0.5f,
  -0.5f,  0.5f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, square);

  glColor3ub(0, 120, 255);
  glDrawArrays(GL_QUADS, 0, 4);

  glColor3ub(255, 255, 255);
  glLineWidth(3.0f);
  glDrawArrays(GL_LINE_LOOP, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_04 - Square Plus Outline");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
