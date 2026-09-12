#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 04 — GL LINE STRIP
 *
 * Task: Use one GL_LINE_STRIP to draw an orange mountain silhouette with five vertices.
 */

#include "common.h"

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.647f, 0.0f);
    glLineWidth(10.0f);

    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.9f, 0.0f);
        glVertex2f(-0.45f, 0.4f);                
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.45f, 0.4f);  
        glVertex2f(0.9f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutCreateWindow("Exercise 4");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}