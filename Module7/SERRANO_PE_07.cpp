#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float angle = 0.0f;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glColor3f(0.3f, 0.8f, 1.0f);
  glBegin(GL_QUADS);
  glVertex2f(-0.4f, -0.4f);
  glVertex2f( 0.4f, -0.4f);
  glVertex2f( 0.4f,  0.4f);
  glVertex2f(-0.4f,  0.4f);
  glEnd();
  glFlush();
}

void animateQuad(int value) {
  (void)value;
  angle += 2.0f;
  if (angle >= 360.0f) angle = 0.0f;
  glutPostRedisplay();
  glutTimerFunc(16, animateQuad, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_07 - Animated Rotating Quad");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glutTimerFunc(16, animateQuad, 0);
  glutMainLoop();
  return 0;
}
