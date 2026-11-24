#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor3f(0.3f, 0.8f, 0.5f);
  glBegin(GL_TRIANGLES);
  glVertex2f(2.0f, 2.3f);
  glVertex2f(1.0f, 0.7f);
  glVertex2f(3.0f, 0.7f);
  glEnd();
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_05 - Asymmetric Ortho Box");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 4.0, 0.0, 3.0, -1.0, 1.0);
  glutMainLoop();
  return 0;
}
