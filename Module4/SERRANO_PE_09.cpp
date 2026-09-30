#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#define PI M_PI
#define FULL_TURN 2.0f*PI
#define QUARTER_TURN FULL_TURN/4.0f

const int VERTEX_COUNT = 6;

GLfloat vertices[VERTEX_COUNT * 2];

// Compute vertices of the pentagon
void computePentagon(float x, float y, float radius, GLfloat *arr) {
  const int segments = 5;

  // Vertex 0 is the shared center of the triangle fan.
  arr[0] = x;
  arr[1] = y;

  // Vertices 1-5 form the pentagon's outer ring.
  for (int i = 0; i < segments; i++) {
    float angle = (float)i / segments * FULL_TURN + QUARTER_TURN;
    int offset = (i + 1) * 2;
    arr[offset] = x + radius * cosf(angle);
    arr[offset + 1] = y + radius * sinf(angle);
  }
}

GLuint indices[] = {0, 1, 2, 3, 4, 5, 1};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  computePentagon(0.0f, 0.0f, 0.65f, vertices);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  glColor3ub(180, 100, 255);
  glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_09 - Indexed Triangle Fan Pentagon");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
