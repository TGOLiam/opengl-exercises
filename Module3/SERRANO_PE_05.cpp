#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

struct Position{
    float x,y;
};

struct Color{
    float r,g,b;
};

void drawString(const char *str, Position base, Color c, void *font){
    glColor3f(c.r, c.g, c.b);
    glRasterPos2f(base.x, base.y);

    for (const char *c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


int button_state = -1;

void mouse(int button, int state, int, int){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    button_state = GLUT_LEFT_BUTTON;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    button_state = GLUT_RIGHT_BUTTON;
  }

  glutPostRedisplay();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  Color c;

  std::string msg;

  switch(button_state){
    case -1:
      c = {1.0f, 1.0f, 1.0f};
      msg = "Click the mouse buttons";
      break;
    case GLUT_LEFT_BUTTON:
      c = {0.0f, 1.0f, 0.0f};
      msg = "You clicked the left mouse button";
      break;
    case GLUT_RIGHT_BUTTON:
      c = {1.0f, 0.0f, 0.0f};
      msg = "You clicked the right mouse button";
      break;
  }

  Position p = {-0.3f, 0.0f};
  if (button_state == GLUT_LEFT_BUTTON || button_state == GLUT_RIGHT_BUTTON)
    p.x = -0.5f;

  drawString(
    msg.c_str(),
    p,
    c,
    GLUT_BITMAP_HELVETICA_18
  );

  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_05 - Mouse Button Text Color");
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
