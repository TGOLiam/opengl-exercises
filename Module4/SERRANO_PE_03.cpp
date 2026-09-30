#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat lines[] = {
  -0.8f,  0.5f,
   0.8f,  0.5f,
  -0.8f, -0.5f,
   0.8f, -0.5f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glColor3ub(255, 255, 255);
  glVertexPointer(2, GL_FLOAT, 0, lines);
  glDrawArrays(GL_LINES, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_03 - Two Lines, One Array");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
