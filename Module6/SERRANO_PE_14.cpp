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

GLuint shapeVBO;
GLfloat vertices[] = {0, 0.7f, 0, -0.67f, 0.22f, 0, -0.41f, -0.57f, 0, 0.41f, -0.57f, 0, 0.67f, 0.22f, 0};
GLfloat colors[] = {1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0.5f, 1, 1, 0, 1};
void buildShape() {
  glGenBuffers(1, &shapeVBO);
  glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void *)sizeof(vertices));
  glBegin(GL_POLYGON);
  for (int i = 0; i < 5; i++) glArrayElement(i);
  glEnd();
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_14 - Colored Pentagon");
  glutDisplayFunc(display);
  
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif
  buildShape();
  glutMainLoop();
  return 0;
}
