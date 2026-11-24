#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLuint quadVBO;

void scaleAll(GLfloat *mapV, float scale) {
  GLfloat matrix[] = {
    scale, 0.0f,  0.0f,  0.0f,
    0.0f,  scale, 0.0f,  0.0f,
    0.0f,  0.0f,  scale, 0.0f,
    0.0f,  0.0f,  0.0f,  1.0f,
  };

  for (int i = 0; i < 12; i += 3) {
    GLfloat vertex[] = {mapV[i], mapV[i + 1], mapV[i + 2], 1.0f};
    GLfloat result[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
        result[row] += matrix[row * 4 + col] * vertex[col];
      }
    }

    mapV[i] = result[0];
    mapV[i + 1] = result[1];
    mapV[i + 2] = result[2];
  }
}

void buildQuad() {
  GLfloat quad[] = {
    -0.3f, -0.3f, 0.0f,
     0.3f, -0.3f, 0.0f,
     0.3f,  0.3f, 0.0f,
    -0.3f,  0.3f, 0.0f,
  };

  glGenBuffers(1, &quadVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

  GLfloat *mapped = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
  if (mapped != 0) {
    scaleAll(mapped, 2.0f);
    glUnmapBuffer(GL_ARRAY_BUFFER);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3f(0.2f, 0.8f, 1.0f);
  glDrawArrays(GL_QUADS, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_08 - Scale VBO Quad");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildQuad();
  glutMainLoop();
  return 0;
}
