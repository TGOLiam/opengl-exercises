#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 05 — GL LINE LOOP
 *
 * Task: Draw a cyan diamond outline with GL_LINE_LOOP and a line width of 4.
 */

#include "common.h"

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 1.0f);
    glLineWidth(4.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, 0.0f);                
        glVertex2f(0.0f, 0.9f);
        glVertex2f(0.5f, 0.0f);            
        glVertex2f(0.0f, -0.9f);
    glEnd();

    glFlush();
}

int main(int argc, char**argv){
    glutInit(&argc, argv);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutCreateWindow("Exercise 5");

    glutDisplayFunc(display);

    glutMainLoop();
}

