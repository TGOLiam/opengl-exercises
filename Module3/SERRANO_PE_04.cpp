#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct Color{
    float r,g,b;
};

Color bg_color = {0.0f, 0.0f, 0.0f};

void keyboard(unsigned char key, int, int){
  if (key == 'r' || key == 'R') {
    bg_color = {1.0f, 0.0f, 0.0f};
  }
  else if (key == 'g' || key == 'G') {
    bg_color = {0.0f, 1.0f, 0.0f};
  }
  else if (key == 'b' || key == 'B') {
    bg_color = {0.0f, 0.0f, 1.0f};
  }

  glutPostRedisplay();
}

void display() {
  glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_04 - Keyboard Background Color Switch");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
