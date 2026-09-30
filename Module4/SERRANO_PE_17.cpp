#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

#define PI M_PI
#define FULL_TURN 2.0f*PI

const int TEETH = 8;
const int RING_VERTICES = TEETH * 2;
const int VERTEX_COUNT = RING_VERTICES + 1;

GLfloat vertices[VERTEX_COUNT * 2];
GLuint evenIndices[TEETH * 3];
GLuint oddIndices[TEETH * 3];

void buildGear() {
  const float outer_radius = 0.72f;
  const float inner_radius = 0.52f;

  vertices[0] = 0.0f;
  vertices[1] = 0.0f;

  for (int i = 0; i < RING_VERTICES; i++) {
    float angle = (float)i / RING_VERTICES * FULL_TURN;
    float radius;
    int offset = (i + 1) * 2;

    if (i % 2 == 0) {
      radius = outer_radius;
    } else {
      radius = inner_radius;
    }

    vertices[offset] = radius * cosf(angle);
    vertices[offset + 1] = radius * sinf(angle);
  }

  for (int i = 0; i < TEETH; i++) {
    int first = 1 + (i * 2);
    int second = 1 + ((i * 2 + 1) % RING_VERTICES);

    if (i % 2 == 0) {
      int index = (i / 2) * 3;
      evenIndices[index] = 0;
      evenIndices[index + 1] = first;
      evenIndices[index + 2] = second;
    } else {
      int index = (i / 2) * 3;
      oddIndices[index] = 0;
      oddIndices[index + 1] = first;
      oddIndices[index + 2] = second;
    }
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glColor3ub(255, 170, 30);
  glDrawElements(GL_TRIANGLES, TEETH * 3 / 2, GL_UNSIGNED_INT, evenIndices);

  glColor3ub(80, 150, 255);
  glDrawElements(GL_TRIANGLES, TEETH * 3 / 2, GL_UNSIGNED_INT, oddIndices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_17 - Procedural Gear Shape");
  buildGear();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
