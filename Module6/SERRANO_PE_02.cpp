#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLfloat topFace[] = {
   0.6f, 0.6f, -0.6f,
  -0.6f, 0.6f, -0.6f,
  -0.6f, 0.6f,  0.6f,
   0.6f, 0.6f,  0.6f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

  GLuint topFaceVBO;
  glGenBuffers(1, &topFaceVBO);
  glBindBuffer(GL_ARRAY_BUFFER, topFaceVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(topFace), topFace, GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3f(0.2f, 0.8f, 0.4f);
  glDrawArrays(GL_QUADS, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &topFaceVBO);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_02 - VBO Cube Top Face");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  glutMainLoop();
  return 0;
}
