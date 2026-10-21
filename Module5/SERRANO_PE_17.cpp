#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>

#define PI M_PI
#define FULL_TURN 2.0f * PI

const int DASH_COUNT = 30;
const int VERTEX_COUNT = DASH_COUNT * 2;

GLuint dashVBO;

void buildDashes() {
  GLfloat dashes[VERTEX_COUNT * 2];
  const float inner_radius = 0.62f;
  const float outer_radius = 0.78f;
  const float angle_step = FULL_TURN / DASH_COUNT;

  for (int i = 0; i < DASH_COUNT; i++) {
    float angle = i * angle_step;
    int offset = i * 4;

    dashes[offset] = inner_radius * cosf(angle);
    dashes[offset + 1] = inner_radius * sinf(angle);
    dashes[offset + 2] = outer_radius * cosf(angle);
    dashes[offset + 3] = outer_radius * sinf(angle);
  }

  glGenBuffers(1, &dashVBO);
  glBindBuffer(GL_ARRAY_BUFFER, dashVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(dashes), dashes, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, dashVBO);
  glVertexPointer(2, GL_FLOAT, 0, 0);
  glColor3ub(255, 180, 50);
  glLineWidth(3.0f);
  glDrawArrays(GL_LINES, 0, VERTEX_COUNT);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_17 - Procedural VBO Dash Ring");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildDashes();
  glutMainLoop();
  return 0;
}
