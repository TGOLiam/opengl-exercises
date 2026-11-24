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



// Illustrates the lecture's Left-Hand vs Right-Hand slide using winding
// order: the same three points listed clockwise vs counter-clockwise
// face the camera differently once back-face culling is enabled.
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Left triangle: counter-clockwise winding (front-facing, right-hand rule)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.8f, -0.3f);
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.6f, 0.3f);
    glEnd();

    // Right triangle: clockwise winding (back-facing, gets culled -- won't draw)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.4f, -0.3f);
        glVertex2f(0.8f, -0.3f);
        glVertex2f(0.6f, 0.3f);
    glEnd();

    glDisable(GL_CULL_FACE);
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("simple");
    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if(err == GLEW_OK){
        glutMainLoop();
    }




  #else
      glutMainLoop();
  #endif
  }
