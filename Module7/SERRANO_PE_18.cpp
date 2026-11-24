#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float baseAngle = 0.0f;
float jointAngle = 0.0f;

void drawSegment(float length) {
  glBegin(GL_QUADS);
  glVertex2f(-0.1f, 0.0f);
  glVertex2f( 0.1f, 0.0f);
  glVertex2f( 0.1f, length);
  glVertex2f(-0.1f, length);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, -0.65f, 0.0f);
  glPushMatrix();
  glRotatef(baseAngle, 0.0f, 0.0f, 1.0f);
  glColor3f(0.2f, 0.7f, 1.0f);
  drawSegment(0.65f);
  glPushMatrix();
  glTranslatef(0.0f, 0.65f, 0.0f);
  glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);
  glColor3f(1.0f, 0.5f, 0.2f);
  drawSegment(0.55f);
  glPopMatrix();
  glPopMatrix();
  glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x; (void)y;
  if (key == 'a') baseAngle += 5.0f;
  else if (key == 'A') baseAngle -= 5.0f;
  else if (key == 's') jointAngle += 5.0f;
  else if (key == 'S') jointAngle -= 5.0f;
  else return;
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_18 - Keyboard Two Joint Arm");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glutMainLoop();
  return 0;
}
