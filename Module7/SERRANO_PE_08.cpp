#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

void drawSquare() {
  glBegin(GL_QUADS);
  glVertex2f(-0.15f, -0.15f);
  glVertex2f( 0.15f, -0.15f);
  glVertex2f( 0.15f,  0.15f);
  glVertex2f(-0.15f,  0.15f);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Translation stays at -0.4 because it is written before the scale.
  glPushMatrix();
  glTranslatef(-0.4f, 0.0f, 0.0f);
  glScalef(1.5f, 1.5f, 1.0f);
  glColor3f(0.2f, 0.8f, 1.0f);
  drawSquare();
  glPopMatrix();

  // Translation becomes 0.4 * 1.5 because scale is written first.
  glPushMatrix();
  glScalef(1.5f, 1.5f, 1.0f);
  glTranslatef(0.4f, 0.0f, 0.0f);
  glColor3f(1.0f, 0.4f, 0.2f);
  drawSquare();
  glPopMatrix();
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_08 - Scale and Translate Order");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glutMainLoop();
  return 0;
}
