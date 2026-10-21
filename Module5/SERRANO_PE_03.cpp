#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat hexagon[] = {
   0.0f,  0.7f, 0.0f,
   0.6f,  0.35f, 0.0f,
   0.6f, -0.35f, 0.0f,
   0.0f, -0.7f, 0.0f,
  -0.6f, -0.35f, 0.0f,
  -0.6f,  0.35f, 0.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint hexagonVBO;
  glGenBuffers(1, &hexagonVBO);
  glBindBuffer(GL_ARRAY_BUFFER, hexagonVBO);
  // GL_STATIC_DRAW fits geometry uploaded once and never changed.
  glBufferData(GL_ARRAY_BUFFER, sizeof(hexagon), hexagon, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glColor3ub(255, 180, 60);
  glDrawArrays(GL_POLYGON, 0, 6);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &hexagonVBO);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_03 - Static VBO Hexagon");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
