#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>



void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);

    glPointSize(10.0f);
    
    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f); glVertex2f(0.0f, 0.5f);
        glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(0.0f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(-0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.5f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_01");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
