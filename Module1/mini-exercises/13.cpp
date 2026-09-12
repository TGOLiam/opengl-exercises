#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


/*
 * Exercise 13 — Multiple Independent Shapes
 *
 * Task: Compose a sailboat from a hull polygon, triangular sail, and mast line.
 */
#include "common.h"

void display(){
    glClearColor(1.0f, 1.0f,1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // hull
    glColor3f(0.58f, 0.29f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, -0.5f);
        glVertex2f(-0.6f, -0.2f);
        glVertex2f(0.6f, -0.2f);
        glVertex2f(0.6f, -0.5f);
    glEnd();

    
    glFlush();
}

int main(int argc, char**argv){
    glutInit(&argc, argv);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutCreateWindow("Exercise 13");

    glutDisplayFunc(display);

    glutMainLoop();
}