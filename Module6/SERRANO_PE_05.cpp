#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.2f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLES);
  glVertex2f(-0.5f, -0.4f);
  glVertex2f(0.5f, -0.4f);
  glVertex2f(0.0f, 0.5f);
  glEnd();

  glFlush();
}

int main(int argc, char **argv) {
  GLfloat matrixA[] = {1.0f, 2.0f, 3.0f, 4.0f};
  GLfloat matrixB[] = {5.0f, 6.0f, 7.0f, 8.0f};
  GLfloat result[4];

  for (int i = 0; i < 4; i++) {
    result[i] = matrixA[i] + matrixB[i];
  }

  std::cout << "Resulting matrix:" << std::endl;
  std::cout << result[0] << " " << result[1] << std::endl;
  std::cout << result[2] << " " << result[3] << std::endl;

  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_05 - Matrix Addition");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
