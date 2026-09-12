#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 08 — Changing the Background Color
 *
 * Task: Set a pale-blue background, then draw a contrasting black triangle.
 */
#include "common.h"

void display(){
    glClearColor(0.68f, 0.85f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.8f , 0.0f);            
        glVertex2f(0.0f , 0.8f);
        glVertex2f(0.8f , 0.0f);
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