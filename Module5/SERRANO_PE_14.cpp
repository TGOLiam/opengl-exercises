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
#define QUARTER_TURN FULL_TURN / 4.0f

const int SEGMENTS = 5;
const int VERTEX_COUNT = SEGMENTS + 1;

GLfloat vertices[VERTEX_COUNT * 2];
GLubyte indices[] = {0, 1, 2, 3, 4, 5, 1};

GLuint pentagonVBO;
GLuint indexVBO;

void computePentagon(float x, float y, float radius, GLfloat *arr) {
  const float angle_step = FULL_TURN / SEGMENTS;

  arr[0] = x;
  arr[1] = y;

  for (int i = 0; i < SEGMENTS; i++) {
    float angle = QUARTER_TURN + i * angle_step;
    int offset = (i + 1) * 2;
    arr[offset] = x + radius * cosf(angle);
    arr[offset + 1] = y + radius * sinf(angle);
  }
}

void buildPentagon() {
  computePentagon(0.0f, 0.0f, 0.7f, vertices);

  glGenBuffers(1, &pentagonVBO);
  glBindBuffer(GL_ARRAY_BUFFER, pentagonVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &indexVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, pentagonVBO);
  glVertexPointer(2, GL_FLOAT, 0, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

  glColor3ub(180, 100, 255);
  glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, 0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_14 - Indexed VBO Pentagon");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildPentagon();
  glutMainLoop();
  return 0;
}
