#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cmath>

int windowWidth = 800;
int windowHeight = 600;
float orbitAngle = 0.0f;
const float pi = 3.14159265f;

void drawScene() {
  glColor3f(0.3f, 0.8f, 1.0f);
  glutSolidCube(1.0);
  glColor3f(1.0f, 0.5f, 0.2f);
  glPushMatrix();
  glTranslatef(1.2f, 0.0f, 0.0f);
  glutSolidCube(0.4);
  glPopMatrix();
}

void drawView(int x, int width, double eyeX, double eyeZ) {
  glViewport(x, 0, width, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width) / windowHeight, 1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX, 1.5, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawScene();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int halfWidth = windowWidth / 2;
  float radians = orbitAngle * pi / 180.0f;
  drawView(0, halfWidth, 0.0, 4.0);
  drawView(halfWidth, windowWidth - halfWidth,
           4.0f * sinf(radians), 4.0f * cosf(radians));
  glFlush();
}

void reshape(int width, int height) {
  windowWidth = width;
  windowHeight = height > 0 ? height : 1;
  glutPostRedisplay();
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
  glutInitWindowSize(800, 600);
  glutCreateWindow("PE_19 - Two Cameras One Orbiting");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glEnable(GL_DEPTH_TEST);
  glutTimerFunc(30, orbitCamera, 0);
  glutMainLoop();
  return 0;
}
