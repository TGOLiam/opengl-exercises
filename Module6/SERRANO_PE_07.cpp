#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat triangle[] = {
  -0.6f, -0.5f, 0.0f,
   0.6f, -0.5f, 0.0f,
   0.0f,  0.6f, 0.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint triangleVBO;
  glGenBuffers(1, &triangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3f(0.2f, 0.8f, 1.0f);

  glBegin(GL_TRIANGLES);
  glArrayElement(0);
  glArrayElement(1);
  glArrayElement(2);
  glEnd();

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &triangleVBO);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_07 - glArrayElement Triangle");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
