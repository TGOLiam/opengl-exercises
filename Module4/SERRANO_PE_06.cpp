#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat triangle[] = {
   0.0f,  0.7f,
  -0.7f, -0.6f,
   0.7f, -0.6f,
};

GLuint indices[] = {2, 0, 1};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, triangle);

  glColor3ub(100, 220, 120);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_06 - Indexed Triangle");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
