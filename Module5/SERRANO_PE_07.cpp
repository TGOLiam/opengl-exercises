#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat zigzag[] = {
  -0.8f, -0.4f, 0.0f,
  -0.4f,  0.4f, 0.0f,
   0.0f, -0.4f, 0.0f,
   0.4f,  0.4f, 0.0f,
   0.8f, -0.4f, 0.0f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint zigzagVBO;
  glGenBuffers(1, &zigzagVBO);
  glBindBuffer(GL_ARRAY_BUFFER, zigzagVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(zigzag), zigzag, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glColor3ub(255, 220, 80);
  glLineWidth(4.0f);
  glDrawArrays(GL_LINE_STRIP, 0, 5);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &zigzagVBO);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_07 - VBO Line-Strip Zigzag");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
