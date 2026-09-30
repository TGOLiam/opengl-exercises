#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat triangle[] = {
   0.0f,  0.65f,
  -0.6f, -0.5f,
   0.6f, -0.5f,
};

GLfloat quad[] = {
  -0.5f, -0.5f,
   0.5f, -0.5f,
   0.5f,  0.5f,
  -0.5f,  0.5f,
};

GLfloat pentagon[] = {
   0.0f,  0.65f,
   0.62f,  0.2f,
   0.38f, -0.55f,
  -0.38f, -0.55f,
  -0.62f,  0.2f,
};

int currentSelection = 1;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);

  if (currentSelection == 1) {
    glColor3ub(255, 100, 100);
    glVertexPointer(2, GL_FLOAT, 0, triangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  } else if (currentSelection == 2) {
    glColor3ub(100, 180, 255);
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glDrawArrays(GL_QUADS, 0, 4);
  } else {
    glColor3ub(170, 100, 255);
    glVertexPointer(2, GL_FLOAT, 0, pentagon);
    glDrawArrays(GL_POLYGON, 0, 5);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  (void)x;
  (void)y;

  if (key == '1' || key == '2' || key == '3') {
    currentSelection = key - '0';
    glutPostRedisplay();
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_18 - Keyboard-Switched Vertex Arrays");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
