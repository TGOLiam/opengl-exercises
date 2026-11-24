#define GL_SILENCE_DEPRECATION
  #ifdef __APPLE__
  #include <GLUT/glut.h>
  #else
  #include <GL/glew.h>




#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

#define BUFFER_OFFSET(i) ((void*)(i))



// gluOrtho2D(left, right, bottom, top) is a simplified glOrtho for pure
// 2D rendering -- it automatically sets zNear = -1 and zFar = 1.
void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.8f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.4f, -0.4f);
        glVertex2f( 0.4f, -0.4f);
        glVertex2f( 0.4f, 0.4f);
        glVertex2f(-0.4f, 0.4f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("simple");
    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if(err == GLEW_OK){
        init();
        glutMainLoop();
    }
#else
        init();
    glutMainLoop();
#endif
}
