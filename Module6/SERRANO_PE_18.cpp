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
GLfloat triangle[] = {-0.9f, -0.5f, 0, -0.1f, -0.5f, 0, -0.5f, 0.5f, 0};
GLfloat quad[] = {0.1f, -0.5f, 0, 0.9f, -0.5f, 0, 0.9f, 0.5f, 0, 0.1f, 0.5f, 0};
GLfloat triangleColors[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
GLfloat quadColors[] = {1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0.5f, 0};

void buildShapes() {
  glGenBuffers(1, &shapeVBO);
  glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle) + sizeof(quad) + sizeof(triangleColors) + sizeof(quadColors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle), triangle);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle), sizeof(quad), quad);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle) + sizeof(quad), sizeof(triangleColors), triangleColors);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle) + sizeof(quad) + sizeof(triangleColors), sizeof(quadColors), quadColors);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(triangle) + sizeof(quad)));
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glVertexPointer(3, GL_FLOAT, 0, (void *)sizeof(triangle));
  glColorPointer(3, GL_FLOAT, 0, (void *)(sizeof(triangle) + sizeof(quad) + sizeof(triangleColors)));
  glDrawArrays(GL_QUADS, 0, 4);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_18 - Two Shapes One VBO");
  glutDisplayFunc(display);
  
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif
  buildShapes();
  glutMainLoop();
  return 0;
}
