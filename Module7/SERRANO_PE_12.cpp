#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cmath>

float orbitAngle = 0.0f;
const float pi = 3.14159265f;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  float radians = orbitAngle * pi / 180.0f;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(3.0f * sinf(radians), 0.8, 3.0f * cosf(radians),
            0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  // The quad stays fixed; only the camera moves.
  glColor3f(0.2f, 0.7f, 1.0f);
  glBegin(GL_QUADS);
  glVertex3f(-0.8f, -0.6f, 0.0f);
  glVertex3f( 0.8f, -0.6f, 0.0f);
  glVertex3f( 0.8f,  0.6f, 0.0f);
  glVertex3f(-0.8f,  0.6f, 0.0f);
  glEnd();
  glFlush();
}

void orbitCamera(int value) {
  (void)value;
  orbitAngle += 2.0f;
  if (orbitAngle >= 360.0f) orbitAngle = 0.0f;
  glutPostRedisplay();
  glutTimerFunc(30, orbitCamera, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_12 - Orbiting Camera");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 10.0);
  glutTimerFunc(30, orbitCamera, 0);
  glutMainLoop();
  return 0;
}
