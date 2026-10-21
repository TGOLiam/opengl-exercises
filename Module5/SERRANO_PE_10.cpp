#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
GLfloat quad[] = {
  -0.6f, -0.6f, 0.0f,  1.0f, 0.2f, 0.2f,
   0.6f, -0.6f, 0.0f,  0.2f, 1.0f, 0.2f,
   0.6f,  0.6f, 0.0f,  0.2f, 0.4f, 1.0f,
  -0.6f,  0.6f, 0.0f,  1.0f, 0.9f, 0.2f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint quadVBO;
  GLsizei stride = 6 * sizeof(GLfloat);

  glGenBuffers(1, &quadVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, stride, (void *)0);
  glColorPointer(3, GL_FLOAT, stride, (void *)(3 * sizeof(GLfloat)));
  glDrawArrays(GL_QUADS, 0, 4);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &quadVBO);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_10 - Interleaved VBO Quad");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
