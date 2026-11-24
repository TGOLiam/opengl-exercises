// Ex17.cpp - standalone Module 08 example
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
GLuint tex=0;
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,2.5,5, 0,0,0, 0,1,0);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glBindTexture(GL_TEXTURE_2D,tex);
glBegin(GL_QUADS);
glNormal3f(0,0,1);
glTexCoord2f(0,0); glVertex3f(-1.5f,-1.5f,0);
glTexCoord2f(1,0); glVertex3f( 1.5f,-1.5f,0);
glTexCoord2f(1,1); glVertex3f( 1.5f, 1.5f,0);
glTexCoord2f(0,1); glVertex3f(-1.5f, 1.5f,0);
glEnd();
    glutSwapBuffers();
}
void init() {
    glClearColor(.08f,.09f,.12f,1);
    glEnable(GL_DEPTH_TEST);
    glGenTextures(1,&tex);
glBindTexture(GL_TEXTURE_2D,tex);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
unsigned char pixels[]={255,255,255, 0,0,0, 0,0,0, 255,255,255};
glPixelStorei(GL_UNPACK_ALIGNMENT,1);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,2,2,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
glEnable(GL_TEXTURE_2D);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,800.0/600.0,.1,100);
}
int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Module 08 - Ex17");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
