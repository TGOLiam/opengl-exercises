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
  glColor3f(1.0f, 0.6f, 0.2f);
  glBegin(GL_QUADS);
  glVertex2f(300.0f, 240.0f);
  glVertex2f(500.0f, 240.0f);
  glVertex2f(500.0f, 360.0f);
  glVertex2f(300.0f, 360.0f);
  glEnd();
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("PE_06 - Pixel Coordinates");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 800.0, 0.0, 600.0);
  glutMainLoop();
  return 0;
}
