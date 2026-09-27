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
  drawString(
    "SERRANO, LIAM BRENT",
    Position{-0.3f, 0.3f},
    Color{1.0f, 1.0f, 1.0f},
    GLUT_BITMAP_HELVETICA_10
  );
  drawString(
    "SERRANO, LIAM BRENT",
    Position{-0.3f, 0.0f},
    Color{1.0f, 1.0f, 1.0f},
    GLUT_BITMAP_HELVETICA_18
  );
  drawString(
    "SERRANO, LIAM BRENT",
    Position{-0.3f, -0.3f},
    Color{1.0f, 1.0f, 1.0f},
    GLUT_BITMAP_TIMES_ROMAN_24
  );


  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_02 - Font Size Comparison");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
