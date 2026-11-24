#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

bool depthOn = true;

void drawTriangle(float size, float z, float red, float green, float blue) {
  glColor3f(red, green, blue);
  glBegin(GL_TRIANGLES);
  glVertex3f(0.0f, size, z);
  glVertex3f(-size, -size, z);
  glVertex3f( size, -size, z);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (depthOn) glEnable(GL_DEPTH_TEST);
  else glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -3.0f);
  // Drawing far last hides the nearer triangles only when depth testing is off.
  drawTriangle(0.65f,  0.5f, 1.0f, 0.3f, 0.2f);
  drawTriangle(0.85f,  0.0f, 0.2f, 1.0f, 0.4f);
  drawTriangle(1.05f, -0.5f, 0.2f, 0.5f, 1.0f);
  glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x; (void)y;
  if (key == 'd' || key == 'D') {
    depthOn = !depthOn;
    glutPostRedisplay();
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_14 - Three Triangle Depth Toggle");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 10.0);
  glutMainLoop();
  return 0;
}
