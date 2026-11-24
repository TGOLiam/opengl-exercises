#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat linePositions[] = {
  -0.7f, 0.0f, 0.0f,
   0.7f, 0.0f, 0.0f,
};

GLfloat lineColors[] = {
  1.0f, 0.3f, 0.2f,
  0.2f, 0.8f, 1.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint lineVBO;
  glGenBuffers(1, &lineVBO);
  glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(linePositions) + sizeof(lineColors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(linePositions), linePositions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(linePositions), sizeof(lineColors), lineColors);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void *)sizeof(linePositions));
  glLineWidth(4.0f);
  glDrawArrays(GL_LINES, 0, 2);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &lineVBO);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_06 - Colored Line with glBufferSubData");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
