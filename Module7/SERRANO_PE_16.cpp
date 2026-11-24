#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

int windowWidth = 800;
int windowHeight = 600;

void drawCube() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -4.0f);
  glRotatef(25.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.3f, 0.8f, 1.0f);
  glutSolidCube(1.5);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int halfWidth = windowWidth / 2;
  double aspect = double(halfWidth) / windowHeight;

  glViewport(0, 0, halfWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0 * aspect, 2.0 * aspect, -2.0, 2.0, 1.0, 10.0);
  drawCube();

  glViewport(halfWidth, 0, windowWidth - halfWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(windowWidth - halfWidth) / windowHeight, 1.0, 10.0);
  drawCube();
  glFlush();
}

void reshape(int width, int height) {
  windowWidth = width;
  windowHeight = height > 0 ? height : 1;
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("PE_16 - Ortho and Perspective Viewports");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
