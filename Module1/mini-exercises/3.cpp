#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 03 — Drawing a Single Line
 *
 * Task: Draw two independent, thick magenta line segments that form a V shape.
 */

#define W_WIDTH 480
#define W_HEIGHT 320

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0f, 1.0f, 0.004f);
    glLineWidth(25.0f);

    glBegin(GL_LINES);
        glVertex2f(-0.5f, 0.8f);
        glVertex2f(0.0f, -0.7f);

        glVertex2f(0.0f, -0.7f);
        glVertex2f(0.5f, 0.8f);
    glEnd();


    glFlush();
}

int main(int argc, char**argv){

    glutInit(&argc, argv);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutCreateWindow("Exercise 3");

    glutDisplayFunc(display);

    glutMainLoop();


    return 0;
}
