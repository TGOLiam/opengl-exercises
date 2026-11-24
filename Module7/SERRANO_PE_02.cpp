#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -3.0f);
  glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
  glColor3f(0.2f, 0.7f, 1.0f);
  glBegin(GL_QUADS);
  glVertex2f(-0.8f, -0.8f);
  glVertex2f( 0.8f, -0.8f);
  glVertex2f( 0.8f,  0.8f);
  glVertex2f(-0.8f,  0.8f);
  glEnd();
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_02 - Rotate Quad Around X");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 10.0);
  glutMainLoop();
  return 0;
}
