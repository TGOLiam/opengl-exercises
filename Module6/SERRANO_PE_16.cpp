#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdlib>
#include <iostream>

bool culling = false;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(0.2f, 0.8f, 1.0f);
  glVertex2f(-0.9f, -0.5f); glVertex2f(-0.1f, -0.5f); glVertex2f(-0.5f, 0.5f);
  glColor3f(1.0f, 0.4f, 0.2f);
  glVertex2f(0.1f, -0.5f); glVertex2f(0.5f, 0.5f); glVertex2f(0.9f, -0.5f);
  glEnd();
  glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x; (void)y;
  if (key == 'f') {
    culling = !culling;
    if (culling) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
    glutPostRedisplay();
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_16 - Toggle Face Culling");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif
  glCullFace(GL_BACK);
  glutMainLoop();
  return 0;
}
