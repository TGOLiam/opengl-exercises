#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat triangle[] = {
   0.0f,  0.7f, 0.0f,
  -0.7f, -0.5f, 0.0f,
   0.7f, -0.5f, 0.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint triangleVBO;
  glGenBuffers(1, &triangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3ub(100, 220, 130);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Stop OpenGL from reading vertex positions as an array.
  glDisableClientState(GL_VERTEX_ARRAY);
  // Return to normal pointer operation with no VBO bound.
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Release the GPU memory used by this VBO.
  glDeleteBuffers(1, &triangleVBO);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_04 - VBO Cleanup Checklist");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
