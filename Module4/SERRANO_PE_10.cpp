#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Five x-positions and two y-positions create four neighboring quads.
GLfloat vertices[] = {
  -0.9f, -0.3f,
  -0.45f, -0.3f,
   0.0f, -0.3f,
   0.45f, -0.3f,
   0.9f, -0.3f,
  -0.9f,  0.3f,
  -0.45f,  0.3f,
   0.0f,  0.3f,
   0.45f,  0.3f,
   0.9f,  0.3f,
};

GLuint quadIndices[][4] = {
  {0, 1, 6, 5},
  {1, 2, 7, 6},
  {2, 3, 8, 7},
  {3, 4, 9, 8},
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);

  for (int i = 0; i < 4; i++) {
    if (i % 2 == 0) {
      glColor3ub(40, 40, 40);
    } else {
      glColor3ub(230, 230, 230);
    }
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, quadIndices[i]);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_10 - Checkerboard Row");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
