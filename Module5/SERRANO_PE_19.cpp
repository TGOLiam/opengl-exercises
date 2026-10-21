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

GLfloat colorSchemes[][9] = {
  {1.0f, 0.2f, 0.2f,  0.2f, 1.0f, 0.2f,  0.2f, 0.4f, 1.0f},
  {1.0f, 0.8f, 0.1f,  1.0f, 0.2f, 0.7f,  0.4f, 0.2f, 1.0f},
  {0.2f, 1.0f, 0.9f,  0.1f, 0.6f, 1.0f,  0.7f, 1.0f, 0.2f},
};

GLuint positionVBO;
GLuint colorVBO;
int color_scheme = 0;

void buildTriangle() {
  glGenBuffers(1, &positionVBO);
  glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

  glGenBuffers(1, &colorVBO);
  glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colorSchemes[0]), colorSchemes[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
  glColorPointer(3, GL_FLOAT, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x;
  (void)y;

  if (key == 'c') {
    color_scheme = (color_scheme + 1) % 3;
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    GLfloat *mapped = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (mapped != 0) {
      for (int i = 0; i < 9; i++) {
        mapped[i] = colorSchemes[color_scheme][i];
      }
      glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_19 - Keyboard VBO Color Change");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildTriangle();
  glutMainLoop();
  return 0;
}
