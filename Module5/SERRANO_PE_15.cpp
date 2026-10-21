#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLuint quadVBO;
float current_offset = 0.0f;
bool moving_up = true;

void buildQuad() {
  GLfloat quad[] = {
    -0.35f, -0.35f, 0.0f,
     0.35f, -0.35f, 0.0f,
     0.35f,  0.35f, 0.0f,
    -0.35f,  0.35f, 0.0f,
  };

  glGenBuffers(1, &quadVBO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColor3ub(100, 180, 255);
  glDrawArrays(GL_QUADS, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glFlush();
}

void bounceQuad(int value) {
  (void)value;
  const float step = 0.02f;

  if (current_offset >= 0.4f) {
    moving_up = false;
  } else if (current_offset <= -0.4f) {
    moving_up = true;
  }

  float dy = moving_up ? step : -step;
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  GLfloat *mapped = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
  if (mapped != 0) {
    mapped[1] += dy;
    mapped[4] += dy;
    mapped[7] += dy;
    mapped[10] += dy;
    glUnmapBuffer(GL_ARRAY_BUFFER);
    current_offset += dy;
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glutPostRedisplay();
  glutTimerFunc(30, bounceQuad, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_15 - Bouncing VBO Quad");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildQuad();
  glutTimerFunc(30, bounceQuad, 0);
  glutMainLoop();
  return 0;
}
