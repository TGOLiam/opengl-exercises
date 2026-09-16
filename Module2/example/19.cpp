#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/*



 * Example 19 - A Gallery of Stipple Patterns
 * ------------------------------------
 * Concept: Combines glLineWidth, glLineStipple, and per-line color to
 * show several dash/dot styles stacked in one window, so students can
 * compare pattern + repeatFactor + color together.
 */

void drawStippledLine(float y, GLint factor, GLushort pattern, float r, float g, float
b) {
    glColor3f(r, g, b);
    glLineStipple(factor, pattern);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.8f, y);
        glVertex2f( 0.8f, y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0f);
    glEnable(GL_LINE_STIPPLE);

    drawStippledLine( 0.6f, 1, 0x00FF, 1.0f, 1.0f, 1.0f); // white dashes
    drawStippledLine( 0.2f, 1, 0x0C0F, 1.0f, 0.6f, 0.0f); // orange dash-dot
    drawStippledLine(-0.2f, 1, 0xAAAA, 0.2f, 0.8f, 1.0f); // cyan fine dots
    drawStippledLine(-0.6f, 2, 0xAAAA, 1.0f, 0.2f, 0.6f); // pink stretched dots

    glDisable(GL_LINE_STIPPLE);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Ex19 - Stipple Pattern Gallery");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

