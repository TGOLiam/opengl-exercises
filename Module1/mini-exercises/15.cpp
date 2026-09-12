#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 15 — Line Grid
 *
 * Task: Use loops and GL_LINES to draw a blue graph-paper grid with thicker axes.
 */
 #include "common.h"

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(3.5f);
    glBegin(GL_LINES);
        for (float x = -0.8f; x <= 0.8f; x += 0.2f)
        {
            glVertex2f(x, -0.8f);            
            glVertex2f(x, 0.8f);            
        }       

        for (float y = -0.8f; y <= 0.8f; y += 0.2f)
        {
            glVertex2f(-0.8f, y);            
            glVertex2f(0.8f, y);            
        }       
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