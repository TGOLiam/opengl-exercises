#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat triangles[] = {
  -0.65f,  0.35f,
  -0.9f,  -0.3f,
  -0.4f,  -0.3f,

   0.0f,   0.35f,
  -0.25f, -0.3f,
   0.25f, -0.3f,

   0.65f,  0.35f,
   0.4f,  -0.3f,
   0.9f,  -0.3f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, triangles);

  glColor3ub(120, 190, 255);
  glDrawArrays(GL_TRIANGLES, 0, 9);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_08 - Three Triangles, One Array");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
