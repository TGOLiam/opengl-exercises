#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLuint triangleVBO;
GLfloat *mapV;

void translateX(float x, int startindex) {
  mapV[startindex] += x;
}

void buildTriangle() {
  GLfloat triangle[] = {
    -0.7f, -0.4f, 0.0f,
    -0.1f, -0.4f, 0.0f,
    -0.4f,  0.4f, 0.0f,
  };

  glGenBuffers(1, &triangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

  mapV = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
  if (mapV != 0) {
    for (int i = 0; i < 9; i += 3) {
      translateX(0.4f, i);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3f(0.2f, 0.8f, 1.0f);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_04 - Translate X VBO Triangle");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildTriangle();
  glutMainLoop();
  return 0;
}
