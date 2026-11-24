#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

bool wideView = true;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(wideView ? 90.0 : 30.0, 1.0, 1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -4.0f);
  glRotatef(25.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.3f, 0.8f, 1.0f);
  glutSolidCube(1.2);
  glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x; (void)y;
  if (key == 'v' || key == 'V') {
    wideView = !wideView;
    glutPostRedisplay();
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_10 - Wide and Narrow FOV");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
