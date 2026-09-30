#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat pattern[] = {
  0.0f, 0.0f,
  -0.3f, 0.3f,
  -0.3f, -0.3f,
  0.3f, 0.3f,
  0.3f, -0.3f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glColor3ub(255, 255, 255);
  glPointSize(3.0f);
  glVertexPointer(2, GL_FLOAT, 0, pattern);
  glDrawArrays(GL_POINTS, 0, 5);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_01 - Vertex Array X-Pattern Points");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
