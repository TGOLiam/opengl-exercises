#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define W_WIDTH 480
#define W_HEIGHT 320

/*
 * Exercise 02 — Drawing a Single Point
 *
 * Task: Draw three differently sized points at three distinct coordinates.
 */

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    
    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.0f);
    glEnd();

    glPointSize(20.0f);
    glBegin(GL_POINTS);
        glVertex2f(-0.6f, 0.5f);
    glEnd();

    glPointSize(30.0f);
    glBegin(GL_POINTS);
        glVertex2f(0.7f, -0.4f);
    glEnd();

    glFlush();
}


int main(int argc, char**argv){

    glutInit(&argc, argv);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutCreateWindow("Exercise 2");

    glutDisplayFunc(display);

    glutMainLoop();



    return 0;
}