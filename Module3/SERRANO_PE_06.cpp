#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


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

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  // Draw string using standard GLUT function

  glBegin(GL_TRIANGLES);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.0f, 0.3f);
  glEnd();

  drawString(
    "This is a white triangle.",
    Position{-0.3f, -0.4f},
    Color{1.0f, 1.0f, 1.0f},
    GLUT_BITMAP_HELVETICA_18
  );


  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_06 - Shape with Caption");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
