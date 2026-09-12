#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 07 — A Filled Square
 *
 * Task: Use GL_POLYGON to draw a wide, filled purple trapezoid.
 */
#include "common.h"

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.3f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, 0.0f);                
        glVertex2f(-0.32f, 0.5f);
        glVertex2f(0.32f, 0.5f);
        glVertex2f(0.8f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char**argv){
    glutInit(&argc, argv);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutCreateWindow("Exercise 6");

    glutDisplayFunc(display);

    glutMainLoop();
}