#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

#define PI M_PI
#define FULL_TURN 2.0f*PI

const int PETAL_COUNT = 8;
const int DISC_SEGMENTS = 24;

GLfloat petalVertices[PETAL_COUNT * 3 * 2];
GLfloat petalColors[PETAL_COUNT * 3 * 3];

GLfloat discVertices[(DISC_SEGMENTS + 2) * 2];
GLuint discIndices[DISC_SEGMENTS + 2];

GLfloat groundVertices[] = {
  -0.95f, -0.75f,
   0.95f, -0.75f,
   0.95f, -0.95f,
  -0.95f, -0.95f,
};

void buildFlower() {
  const float center_x = 0.0f;
  const float center_y = 0.05f;
  const float inner_radius = 0.12f;
  const float petal_radius = 0.62f;

  for (int i = 0; i < PETAL_COUNT; i++) {
    float angle = (float)i / PETAL_COUNT * FULL_TURN;
    float left_angle = angle - 0.35f;
    float right_angle = angle + 0.35f;
    int vertex_offset = i * 6;
    int color_offset = i * 9;
    float red = 0.7f + 0.3f * ((float)i / PETAL_COUNT);
    float blue = 0.9f - 0.5f * ((float)i / PETAL_COUNT);

    petalVertices[vertex_offset] = center_x;
    petalVertices[vertex_offset + 1] = center_y;
    petalVertices[vertex_offset + 2] = center_x + petal_radius * cosf(left_angle);
    petalVertices[vertex_offset + 3] = center_y + petal_radius * sinf(left_angle);
    petalVertices[vertex_offset + 4] = center_x + petal_radius * cosf(right_angle);
    petalVertices[vertex_offset + 5] = center_y + petal_radius * sinf(right_angle);

    for (int j = 0; j < 3; j++) {
      petalColors[color_offset + j * 3] = red;
      petalColors[color_offset + j * 3 + 1] = 0.2f;
      petalColors[color_offset + j * 3 + 2] = blue;
    }
  }

  discVertices[0] = center_x;
  discVertices[1] = center_y;
  discIndices[0] = 0;

  for (int i = 0; i <= DISC_SEGMENTS; i++) {
    float angle = (float)i / DISC_SEGMENTS * FULL_TURN;
    int vertex_offset = (i + 1) * 2;
    discVertices[vertex_offset] = center_x + inner_radius * cosf(angle);
    discVertices[vertex_offset + 1] = center_y + inner_radius * sinf(angle);
    discIndices[i + 1] = i + 1;
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(70, 150, 70);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, groundVertices);
  glDrawArrays(GL_QUADS, 0, 4);

  // Petals are drawn first; the center disc is placed on top afterward.
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, petalVertices);
  glColorPointer(3, GL_FLOAT, 0, petalColors);
  glDrawArrays(GL_TRIANGLES, 0, PETAL_COUNT * 3);

  glDisableClientState(GL_COLOR_ARRAY);

  glColor3ub(255, 190, 40);
  glVertexPointer(2, GL_FLOAT, 0, discVertices);
  glDrawElements(GL_TRIANGLE_FAN, DISC_SEGMENTS + 2, GL_UNSIGNED_INT, discIndices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_20 - Procedural Flower Scene");
  buildFlower();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
