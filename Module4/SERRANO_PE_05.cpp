#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLint triangle[] = {
     0,  300,
  -300, -300,
   300, -300,
};

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_INT, 0, triangle);

  glColor3ub(255, 180, 0);
  glPushMatrix();
  glScalef(0.002f, 0.002f, 1.0f);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glPopMatrix();

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_05 - GLint Vertex Data Type");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
