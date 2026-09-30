#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Left quad: 6 vertices (two triangles, with duplicated corners).
GLfloat arrayQuad[] = {
  -0.85f, -0.35f,
  -0.25f, -0.35f,
  -0.25f,  0.35f,
  -0.85f, -0.35f,
  -0.25f,  0.35f,
  -0.85f,  0.35f,
};

// Right quad: 4 unique vertices and a 6-entry index array.
GLfloat indexedQuad[] = {
   0.25f, -0.35f,
   0.85f, -0.35f,
   0.85f,  0.35f,
   0.25f,  0.35f,
};

GLuint quadIndices[] = {
  0, 1, 2,
  0, 2, 3,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(2, GL_FLOAT, 0, arrayQuad);
  glColor3ub(80, 170, 255);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  glVertexPointer(2, GL_FLOAT, 0, indexedQuad);
  glColor3ub(255, 130, 60);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, quadIndices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_16 - Arrays vs Elements");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
