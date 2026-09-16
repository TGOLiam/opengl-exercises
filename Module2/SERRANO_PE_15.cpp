#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0);  glVertex2f(-0.5f, -0.5f);
        glColor3ub(255, 255, 0);  glVertex2f(-0.5f, 0.5f);
        glColor3ub(255, 255, 255);  glVertex2f(0.5f, 0.5f);
        glColor3ub(255, 0, 255);  glVertex2f(0.5f, -0.5f);
    glEnd();

    
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_15");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
