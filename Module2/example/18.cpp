#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else



#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/*
 * Example 18 - Per-Vertex Color Interpolation on a Triangle
 * ------------------------------------
 * Concept: Giving each of a triangle's three vertices a different
 * color produces a smoothly blended fill across the whole interior.
 */

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

     glBegin(GL_TRIANGLES);
         glColor3ub(92, 181, 100);   glVertex2f(-0.5f, -0.5f); // green
         glColor3f(1.0f, 0.0f, 0.0f); glVertex2f( 0.5f, -0.5f); // red
         glColor3f(0.0f, 0.0f, 1.0f); glVertex2f( 0.0f, 0.5f); // blue
     glEnd();

     glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex18 - Gradient Triangle (Per-Vertex Color)");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

