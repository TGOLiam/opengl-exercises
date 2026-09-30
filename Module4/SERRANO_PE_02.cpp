#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat hexagon[] = {
  0.0f,  0.5f,
  0.433f,  0.25f,
  0.433f, -0.25f,
  0.0f, -0.5f,
 -0.433f, -0.25f,
 -0.433f,  0.25f,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
  glEnableClientState(GL_VERTEX_ARRAY);
  
  glColor3ub(255, 255, 255);
  glPointSize(3.0f);
  glVertexPointer(2, GL_FLOAT, 0, hexagon);
  glDrawArrays(GL_LINE_LOOP, 0, 6);

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_02 - Filled Hexagon via Vertex Array");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
