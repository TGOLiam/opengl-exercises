#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cstdlib>

GLuint shipPositionVBO;
GLuint shipColorVBO;
GLuint groundVBO;
GLuint groundIndexVBO;

float ship_offset = 0.0f;

void buildShip() {
  GLfloat shipPositions[] = {
     0.0f, -0.2f, 0.0f,
    -0.25f, -0.55f, 0.0f,
     0.25f, -0.55f, 0.0f,
  };
  GLfloat shipColors[] = {
    1.0f, 0.3f, 0.2f,
    0.2f, 0.8f, 1.0f,
    1.0f, 0.9f, 0.2f,
  };

  glGenBuffers(1, &shipPositionVBO);
  glBindBuffer(GL_ARRAY_BUFFER, shipPositionVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(shipPositions), shipPositions, GL_DYNAMIC_DRAW);

  glGenBuffers(1, &shipColorVBO);
  glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(shipColors), shipColors, GL_STATIC_DRAW);
}

void buildGround() {
  GLfloat ground[] = {
    -1.0f, -0.65f, 0.0f,
     1.0f, -0.65f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
  };
  GLubyte groundIndices[] = {0, 1, 2, 0, 2, 3};

  glGenBuffers(1, &groundVBO);
  glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STATIC_DRAW);

  glGenBuffers(1, &groundIndexVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices), groundIndices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawGround() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
  glColor3ub(70, 160, 70);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void drawShip() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, shipPositionVBO);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
  glColorPointer(3, GL_FLOAT, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  drawGround();
  drawShip();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glFlush();
}

void moveShip(int value) {
  (void)value;
  const float step = 0.05f;

  glBindBuffer(GL_ARRAY_BUFFER, shipPositionVBO);
  GLfloat *mapped = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
  if (mapped != 0) {
    mapped[0] += step;
    mapped[3] += step;
    mapped[6] += step;
    glUnmapBuffer(GL_ARRAY_BUFFER);
    ship_offset += step;
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glutPostRedisplay();
  glutTimerFunc(1000, moveShip, 0);
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x;
  (void)y;

  if (key == 27) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &shipPositionVBO);
    glDeleteBuffers(1, &shipColorVBO);
    glDeleteBuffers(1, &groundVBO);
    glDeleteBuffers(1, &groundIndexVBO);
    exit(0);
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_20 - Animated Ship Over Indexed Ground");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildShip();
  buildGround();
  glutTimerFunc(1000, moveShip, 0);
  glutMainLoop();
  return 0;
}
