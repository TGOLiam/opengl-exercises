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
    glBegin(GL_TRIANGLES);

    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.6f, 0.34f);
    glVertex2f(-0.4f, 0.0f);
    
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.8f, 0.0f);
    glVertex2f(0.6f, 0.34f);
    glVertex2f(0.4f, 0.0f);
    
    glEnd();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_07");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
