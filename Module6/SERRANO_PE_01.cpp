#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.3f, 0.2f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-0.6f, -0.6f, 0.6f);
  glVertex3f(0.6f, -0.6f, 0.6f);

  glColor3f(0.2f, 0.8f, 1.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.6f, -0.6f, 0.6f);
  glVertex3f(0.6f, -0.6f, -0.6f);

  glColor3f(1.0f, 0.9f, 0.2f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.6f, -0.6f, -0.6f);
  glVertex3f(-0.6f, -0.6f, -0.6f);

  glColor3f(0.4f, 0.9f, 0.4f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-0.6f, -0.6f, -0.6f);
  glVertex3f(-0.6f, -0.6f, 0.6f);
  glEnd();

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_01 - Four-Sided Pyramid");
  glEnable(GL_DEPTH_TEST);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
