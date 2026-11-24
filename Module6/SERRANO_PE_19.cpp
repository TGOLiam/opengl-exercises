#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>
#include <cstdlib>
#include <iostream>

GLuint shapeVBO;
GLfloat vertices[] = {
  -0.4f, -0.4f, 0.0f,  0.4f, -0.4f, 0.0f,
   0.4f,  0.4f, 0.0f, -0.4f,  0.4f, 0.0f,
};
GLfloat colors[] = {1, 0.3f, 0.2f, 0.2f, 0.8f, 1, 1, 0.9f, 0.2f, 0.4f, 0.9f, 0.4f};
void applyMatrix(GLfloat *vertex, const GLfloat *matrix) {
  GLfloat input[] = {vertex[0], vertex[1], vertex[2], 1.0f};
  GLfloat result[] = {0.0f, 0.0f, 0.0f, 0.0f};
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      result[row] += matrix[row * 4 + col] * input[col];
    }
  }
  for (int i = 0; i < 3; i++) {
    vertex[i] = result[i];
  }
}

void rotateZ(GLfloat *vertex, float degrees) {
  float angle = degrees * 3.14159265f / 180.0f;
  float c = cosf(angle);
  float s = sinf(angle);
  GLfloat matrix[] = {c, -s, 0, 0, s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  applyMatrix(vertex, matrix);
}

void translate(GLfloat *vertex, float x, float y, float z) {
  GLfloat matrix[] = {1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1};
  applyMatrix(vertex, matrix);
}

void rotateY(GLfloat *vertex, float degrees) {
  float angle = degrees * 3.14159265f / 180.0f;
  float c = cosf(angle);
  float s = sinf(angle);
  GLfloat matrix[] = {c, 0, s, 0, 0, 1, 0, 0, -s, 0, c, 0, 0, 0, 0, 1};
  applyMatrix(vertex, matrix);
}

void buildShape() {
  glGenBuffers(1, &shapeVBO);
  glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void *)sizeof(vertices));
  glDrawArrays(GL_QUADS, 0, 4);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glFlush();
}

void rotateQuad(int value) {
  (void)value;
  glBindBuffer(GL_ARRAY_BUFFER, shapeVBO);
  GLfloat *mapped = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
  if (mapped != 0) {
    for (int i = 0; i < 12; i += 3) {
      rotateY(&mapped[i], 15.0f);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glutPostRedisplay();
  glutTimerFunc(1000, rotateQuad, 0);
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x;
  (void)y;
  if (key == 27) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &shapeVBO);
    exit(0);
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_19 - Rotating Quad with Cleanup");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif
  buildShape();
  glutTimerFunc(1000, rotateQuad, 0);
  glutMainLoop();
  return 0;
}
