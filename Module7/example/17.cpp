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




// Three independent copies of the same shape, each with its OWN
// glPushMatrix()/glPopMatrix() pair, so each object's transform never
// leaks into the next one's.
void drawTriangle(){
    glBegin(GL_TRIANGLES);
        glVertex2f( 0.0f, 0.15f);
        glVertex2f(-0.15f, -0.15f);
        glVertex2f( 0.15f, -0.15f);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(-0.6f, 0.0f, 0.0f);
        glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
        glColor3f(0.9f, 0.2f, 0.2f);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glColor3f(0.2f, 0.9f, 0.2f);
        drawTriangle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.6f, 0.0f, 0.0f);
        glScalef(1.5f, 1.5f, 1.0f);
        glColor3f(0.2f, 0.2f, 0.9f);
        drawTriangle();
    glPopMatrix();

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
          glutMainLoop();
      }
  #else
      glutMainLoop();
  #endif
  }
