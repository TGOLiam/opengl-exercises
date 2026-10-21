#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat hexagon[] = {
   0.0f,  0.7f, 0.0f,  1.0f, 0.2f, 0.2f,
   0.6f,  0.35f, 0.0f,  1.0f, 0.7f, 0.1f,
   0.6f, -0.35f, 0.0f,  0.2f, 0.8f, 0.2f,
   0.0f, -0.7f, 0.0f,  0.1f, 0.7f, 1.0f,
  -0.6f, -0.35f, 0.0f,  0.3f, 0.2f, 1.0f,
  -0.6f,  0.35f, 0.0f,  0.9f, 0.2f, 0.8f,
};

GLubyte indices[] = {0, 1, 2, 3, 4, 5};

GLuint hexagonVBO;
GLuint indexVBO;

void buildHexagon() {
  glGenBuffers(1, &hexagonVBO);
  glBindBuffer(GL_ARRAY_BUFFER, hexagonVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(hexagon), hexagon, GL_STATIC_DRAW);

  glGenBuffers(1, &indexVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  GLsizei stride = 6 * sizeof(GLfloat);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, hexagonVBO);
  glVertexPointer(3, GL_FLOAT, stride, (void *)0);
  glColorPointer(3, GL_FLOAT, stride, (void *)(3 * sizeof(GLfloat)));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, 0);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_18 - Interleaved Indexed VBO Hexagon");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildHexagon();
  glutMainLoop();
  return 0;
}
