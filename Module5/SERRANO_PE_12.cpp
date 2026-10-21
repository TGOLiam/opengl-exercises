#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

GLuint pointVBO;

void buildPoint() {
  GLfloat point[] = {-0.8f, 0.0f, 0.0f};

  glGenBuffers(1, &pointVBO);
  glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glColor3ub(255, 220, 80);
  glPointSize(15.0f);
  glDrawArrays(GL_POINTS, 0, 1);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glFlush();
}

void movePoint(int value) {
  (void)value;

  glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
  GLfloat *mapped = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
  if (mapped != 0) {
    mapped[0] += 0.1f;
    glUnmapBuffer(GL_ARRAY_BUFFER);
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glutPostRedisplay();
  glutTimerFunc(1000, movePoint, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_12 - Timer VBO Moving Point");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildPoint();
  glutTimerFunc(1000, movePoint, 0);
  glutMainLoop();
  return 0;
}
