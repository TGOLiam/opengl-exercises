#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

void drawSegment(float length) {
  glBegin(GL_QUADS);
  glVertex2f(-0.07f, 0.0f);
  glVertex2f( 0.07f, 0.0f);
  glVertex2f( 0.07f, length);
  glVertex2f(-0.07f, length);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, -0.55f, 0.0f);

  glPushMatrix();
  glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.2f, 0.7f, 1.0f);
  drawSegment(0.4f);

  glPushMatrix();
  glTranslatef(0.0f, 0.4f, 0.0f);
  glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(1.0f, 0.5f, 0.2f);
  drawSegment(0.35f);

  glPushMatrix();
  glTranslatef(0.0f, 0.35f, 0.0f);
  glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.4f, 1.0f, 0.4f);
  drawSegment(0.3f);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_09 - Three Segment Chain");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glutMainLoop();
  return 0;
}
