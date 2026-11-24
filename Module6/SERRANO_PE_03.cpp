#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

GLfloat point[] = {0.3f, 0.2f};
GLfloat scaledPoint[2];

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glPointSize(10.0f);
  glBegin(GL_POINTS);
  glColor3f(1.0f, 0.3f, 0.2f);
  glVertex2f(point[0], point[1]);
  glColor3f(0.2f, 0.8f, 1.0f);
  glVertex2f(scaledPoint[0], scaledPoint[1]);
  glEnd();

  glFlush();
}

int main(int argc, char **argv) {
  GLfloat scalarMatrix[] = {2.0f, 0.0f, 0.0f, 2.0f};
  scaledPoint[0] = scalarMatrix[0] * point[0] + scalarMatrix[1] * point[1];
  scaledPoint[1] = scalarMatrix[2] * point[0] + scalarMatrix[3] * point[1];

  std::cout << "Before: (" << point[0] << ", " << point[1] << ")" << std::endl;
  std::cout << "After: (" << scaledPoint[0] << ", " << scaledPoint[1] << ")" << std::endl;

  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_03 - Scalar Product Matrix");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
