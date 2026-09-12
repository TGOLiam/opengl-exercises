#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 10 — Per Vertex Color
 *
 * Task: Draw a four-vertex diamond whose corners use four different colors.
 */
#include "common.h"

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);     glVertex2f(-0.4f , 0.0f);            
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f , 0.6f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.4f , 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(0.0f , -0.6f);
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