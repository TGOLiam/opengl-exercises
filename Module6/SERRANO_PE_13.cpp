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

void rotateZ(GLfloat *vector, float degrees) {
  float angle = degrees * 3.14159265f / 180.0f;
  float c = cosf(angle);
  float s = sinf(angle);
  GLfloat matrix[] = {c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  GLfloat result[] = {0, 0, 0, 0};
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) result[row] += matrix[row * 4 + col] * vector[col];
  }
  for (int i = 0; i < 4; i++) vector[i] = result[i];
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_13 - Rotation and Homogeneous Coordinates");
  glutDisplayFunc(display);
  
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif
  GLfloat position[] = {1, 0, 0, 1};
  GLfloat direction[] = {1, 0, 0, 0};
  // Rotation mixes spatial coordinates independently of w; translation is multiplied by w.
  rotateZ(position, 45.0f);
  rotateZ(direction, 45.0f);
  std::cout << "Position: " << position[0] << ", " << position[1] << ", " << position[2] << ", " << position[3] << std::endl;
  std::cout << "Direction: " << direction[0] << ", " << direction[1] << ", " << direction[2] << ", " << direction[3] << std::endl;
  glutMainLoop();
  return 0;
}
