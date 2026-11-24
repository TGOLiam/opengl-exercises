#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cstdlib>

GLuint pyramidVBO = 0;
float angle = 0.0f;
GLfloat positions[] = {
   0.0f, 1.0f, 0.0f, -1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f,
   0.0f, 1.0f, 0.0f,  1.0f,-1.0f, 1.0f,  1.0f,-1.0f,-1.0f,
   0.0f, 1.0f, 0.0f,  1.0f,-1.0f,-1.0f, -1.0f,-1.0f,-1.0f,
   0.0f, 1.0f, 0.0f, -1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f
};
GLfloat colors[] = {
  1,0,0, 0,1,0, 0,0,1,
  1,0,0, 0,0,1, 0,1,0,
  1,0,0, 0,1,0, 0,0,1,
  1,0,0, 0,0,1, 0,1,0
};

void buildPyramid() {
  glGenBuffers(1, &pyramidVBO);
  glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef(angle, 1.0f, 0.0f, 0.0f);
  glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void *)sizeof(positions));
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 12; i++) glArrayElement(i);
  glEnd();
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glFlush();
}

void animatePyramid(int value) {
  (void)value;
  angle += 2.0f;
  if (angle >= 360.0f) angle = 0.0f;
  glutPostRedisplay();
  glutTimerFunc(30, animatePyramid, 0);
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x; (void)y;
  if (key == 27) {
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &pyramidVBO);
    exit(0);
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_15 - Rotating X Axis Pyramid");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 10.0);
  buildPyramid();
  glutTimerFunc(30, animatePyramid, 0);
  glutMainLoop();
  return 0;
}
