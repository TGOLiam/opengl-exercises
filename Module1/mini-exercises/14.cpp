#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 14 — Field of Points
 *
 * Task: Use nested loops to make a 7x5 field of alternating red and white points.
 */
 #include "common.h"

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(10.0f);

    int i = 0;

    glBegin(GL_POINTS);
        for (float x = -0.8f; x <= 0.8f; x += 0.2f) {
            for (float y = -0.8f; y <= 0.8f; y += 0.2f) {
                
                if (i % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
                else glColor3f(1.0f, 1.0f, 0.0f);
                
                glVertex2f(x, y);   
                i++;
            }

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