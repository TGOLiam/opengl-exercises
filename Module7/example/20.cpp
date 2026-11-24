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



// Capstone: a hierarchical two-segment "arm" (glPushMatrix()/glPopMatrix())
// that both rotates as a whole and animates its second segment, viewed
// through gluPerspective + gluLookAt, with GLUT_DEPTH enabled, an error
// callback registered, and ESC-key cleanup.
float wholeAngle = 0.0f;
float armAngle = 0.0f;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                 GLenum severity, GLsizei length,
                                 const GLchar* message, const void* userParam){
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 800.0/600.0, 1.0, 10.0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0,0.0,4.0, 0.0,0.0,0.0, 0.0,1.0,0.0);

   glPushMatrix();
       glRotatef(wholeAngle, 0.0f, 1.0f, 0.0f);

       // Base segment
       glColor3f(0.3f, 0.6f, 0.9f);
       glBegin(GL_QUADS);
           glVertex3f(-0.15f, -0.6f, 0.0f);





           glVertex3f( 0.15f, -0.6f, 0.0f);
           glVertex3f( 0.15f, 0.0f, 0.0f);
           glVertex3f(-0.15f, 0.0f, 0.0f);
       glEnd();

        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.0f);
            glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
            glColor3f(0.9f, 0.4f, 0.2f);
            glBegin(GL_QUADS);
                glVertex3f(-0.12f, 0.0f, 0.0f);
                glVertex3f( 0.12f, 0.0f, 0.0f);
                glVertex3f( 0.12f, 0.6f, 0.0f);
                glVertex3f(-0.12f, 0.6f, 0.0f);
            glEnd();
        glPopMatrix();
    glPopMatrix();

    glFlush();
}

void animate(int value){
    wholeAngle += 1.0f;
    armAngle += 2.0f;
    if(wholeAngle > 360) wholeAngle = 0;
    if(armAngle > 360) armAngle = 0;
    glutPostRedisplay();
    glutTimerFunc(50, animate, 0);
}

void monitorKeyboard(unsigned char key, int x, int y){
    if(key == 27){
        exit(0);
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if(err == GLEW_OK){
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
        init();
        glutTimerFunc(50, animate, 0);
        glutMainLoop();




    }
#else
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
        init();
        glutTimerFunc(50, animate, 0);
    glutMainLoop();
#endif
}
