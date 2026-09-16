#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;



/*
 * Example 12 - GL_QUADS
 * ------------------------------------
 * Concept: Draws individual convex quadrilaterals. OpenGL renders a
 * quad for each group of FOUR vertices - one glBegin/glEnd block can
 * contain several independent quads.
 */

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

     glBegin(GL_QUADS);
         // quad 1 - top rectangle
         glVertex2f(-0.2f, 0.2f);
         glVertex2f(-0.5f, -0.2f);
         glVertex2f(0.5f, -0.2f);
         glVertex2f(0.2f, 0.2f);

         // quad 2 - small square, upper right
         glVertex2f(0.6f, 0.4f);
         glVertex2f(0.0f, 0.4f);
         glVertex2f(0.0f, 0.6f);
         glVertex2f(0.6f, 0.6f);
     glEnd();

     glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex12 - Two Independent Quads (GL_QUADS)");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

