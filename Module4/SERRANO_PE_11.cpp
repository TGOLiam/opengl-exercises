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

const int VERTEX_COUNT = 62;
const int COMPONENTS = 3;

GLfloat vertices[VERTEX_COUNT * 2];
GLfloat colors[VERTEX_COUNT * COMPONENTS];

void drawCircle(float x, float y, float radius, GLfloat *vertex_arr,
                GLfloat *color_arr) {
  const int segments = 60;

  vertex_arr[0] = x;
  vertex_arr[1] = y;
  color_arr[0] = 1.0f;
  color_arr[1] = 1.0f;
  color_arr[2] = 1.0f;

  for (int i = 0; i <= segments; i++) {
    float angle = (float)i / segments * FULL_TURN + QUARTER_TURN;
    int vertex_offset = (i + 1) * 2;
    int color_offset = (i + 1) * 3;
    float t = (float)i / segments;
    float shade;

    if (t <= 0.5f) {
      shade = t * 2.0f;
    } else {
      shade = (1.0f - t) * 2.0f;
    }

    vertex_arr[vertex_offset] = x + radius * cosf(angle);
    vertex_arr[vertex_offset + 1] = y + radius * sinf(angle);

    // Orange -> white -> orange.
    color_arr[color_offset] = 1.0f;
    color_arr[color_offset + 1] = 0.45f + 0.55f * shade;
    color_arr[color_offset + 2] = shade;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  drawCircle(0.0f, 0.0f, 0.7f, vertices, colors);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);
  glDrawArrays(GL_TRIANGLE_FAN, 0, VERTEX_COUNT);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_11 - Procedural Shaded Circle");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
