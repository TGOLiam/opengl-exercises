#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat pattern[] = {
   0.0f,  0.0f, 0.0f,
  -0.5f,  0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
   0.5f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint pointVBO;
  glGenBuffers(1, &pointVBO);
  glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pattern), pattern, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glColor3ub(255, 255, 255);
  glPointSize(10.0f);
  glDrawArrays(GL_POINTS, 0, 5);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &pointVBO);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_01 - VBO X-Pattern Points");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}

