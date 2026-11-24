// Ex14.cpp - standalone Module 08 example
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
GLuint tex=0;
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,2.5,5, 0,0,0, 0,1,0);
    GLfloat pos[]={0,3,0,1}; glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glutSolidSphere(1,40,30);
    glutSwapBuffers();
}
void init() {
    glClearColor(.08f,.09f,.12f,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); GLfloat dir[]={0,-1,0}; glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,dir); glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,25);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,800.0/600.0,.1,100);
}
int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Module 08 - Ex14");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
