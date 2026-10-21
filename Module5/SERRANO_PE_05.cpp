#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat leftTriangle[] = {
  -0.9f, -0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  -0.7f,  0.5f, 0.0f,
};

GLfloat rightTriangle[] = {
   0.5f, -0.5f, 0.0f,
   0.9f, -0.5f, 0.0f,
   0.7f,  0.5f, 0.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint leftTriangleVBO;
  GLuint rightTriangleVBO;

  glGenBuffers(1, &leftTriangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, leftTriangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(leftTriangle), leftTriangle, GL_STATIC_DRAW);

  glGenBuffers(1, &rightTriangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, rightTriangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rightTriangle), rightTriangle, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, leftTriangleVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3ub(255, 120, 100);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBindBuffer(GL_ARRAY_BUFFER, rightTriangleVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3ub(100, 180, 255);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &leftTriangleVBO);
  glDeleteBuffers(1, &rightTriangleVBO);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_05 - Two Separate VBOs");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
