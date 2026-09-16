#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/*
 * Example 16 - glColor4f and Alpha Blending
 * ------------------------------------



 * Concept: glColor4f(r, g, b, alpha) adds a fourth component that
 * controls opacity: 1.0 is fully opaque, 0.0 is fully transparent.
 * Alpha only has a visible effect once blending is turned on with
 * glEnable(GL_BLEND) and a blend function is chosen.
 */

void display() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     glColor4f(1.0f, 0.0f, 0.0f, 0.6f);          // 60% opaque red
     glBegin(GL_QUADS);
         glVertex2f(-0.5f, -0.3f);
         glVertex2f( 0.1f, -0.3f);
         glVertex2f( 0.1f, 0.3f);
         glVertex2f(-0.5f, 0.3f);
     glEnd();

     glColor4f(0.0f, 0.4f, 1.0f, 0.6f);          // 60% opaque blue, overlapping
     glBegin(GL_QUADS);
         glVertex2f(-0.1f, -0.3f);
         glVertex2f( 0.5f, -0.3f);
         glVertex2f( 0.5f, 0.3f);
         glVertex2f(-0.1f, 0.3f);
     glEnd();

     glDisable(GL_BLEND);
     glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Ex16 - Alpha Blending (glColor4f)");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

