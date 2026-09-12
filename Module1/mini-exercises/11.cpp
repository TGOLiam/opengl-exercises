#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 11 — Window Size and Position
 *
 * Task: Create an 800x450 window at (120, 80) and draw a centered rectangle outline.
 */

 #include "common.h"

void display(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.9f , -0.9f);            
        glVertex2f(-0.9f , 0.9f);            
        glVertex2f(0.9f , 0.9f);            
        glVertex2f(0.9f , -0.9f);            
    glEnd();


    glFlush();
}

int main(int argc, char**argv){
    glutInit(&argc, argv);

    glutInitWindowSize(800, 450);
    glutInitWindowPosition(120, 80);


    glutCreateWindow("Exercise 6");

    glutDisplayFunc(display);

    glutMainLoop();
}