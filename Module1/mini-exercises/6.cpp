#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 06 — A Filled Triangle
 *
 * Task: Draw two separate filled triangles: one small red and one large yellow.
 */
#include "common.h"

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.8f, 0.0f);                
        glVertex2f(-0.6f, 0.4f);
        glVertex2f(-0.4f, 0.0f);            
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);                
        glVertex2f(0.4f, 0.8f);
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