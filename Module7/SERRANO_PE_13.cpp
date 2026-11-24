#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat positions[] = {
  -0.6f, -0.6f, 0.0f,   0.6f, -0.6f, 0.0f,
   0.6f,  0.6f, 0.0f,  -0.6f,  0.6f, 0.0f
};
GLfloat colors[] = {
  1.0f, 0.2f, 0.2f,  1.0f, 0.8f, 0.2f,
  0.2f, 0.8f, 1.0f,  0.3f, 1.0f, 0.4f
};
GLuint quadVBO = 0;

void buildQuad() {
  glGenBuffers(1, &quadVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void *)sizeof(positions));
  glBegin(GL_QUADS);
  for (int i = 0; i < 4; i++) glArrayElement(i);
  glEnd();
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_13 - Static Color VBO Quad");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  buildQuad();
  glutMainLoop();
  return 0;
}
