#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.64f, 0.0f);

    glBegin(GL_POLYGON);

    glVertex2f(-0.7f, 0.0f);
    glVertex2f(-0.7f, 0.5f);
    glVertex2f(0.7f, 0.5f);
    glVertex2f(0.7f, 0.0f);


    glEnd();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_04");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
