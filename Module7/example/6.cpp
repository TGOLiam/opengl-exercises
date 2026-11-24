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



  // OpenGL applies transformations in REVERSE of the order they're written
  // (each new matrix multiplies onto the current one). This example draws
  // the SAME shape twice to show that translate-then-rotate is NOT the
  // same as rotate-then-translate.
  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);

         // Left: rotate FIRST in code, so translate happens in the rotated frame
         glLoadIdentity();
         glTranslatef(-0.4f, 0.0f, 0.0f);
         glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
         glColor3f(0.9f, 0.4f, 0.1f);
         glBegin(GL_QUADS);
             glVertex2f(-0.15f, -0.15f);
             glVertex2f( 0.15f, -0.15f);
             glVertex2f( 0.15f, 0.15f);
             glVertex2f(-0.15f, 0.15f);
         glEnd();

         // Right: translate FIRST in code, so rotation happens around the origin
         glLoadIdentity();
         glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
         glTranslatef(0.4f, 0.0f, 0.0f);
         glColor3f(0.1f, 0.6f, 0.9f);
         glBegin(GL_QUADS);
             glVertex2f(-0.15f, -0.15f);
             glVertex2f( 0.15f, -0.15f);




           glVertex2f( 0.15f,      0.15f);
           glVertex2f(-0.15f,      0.15f);
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
          glutMainLoop();
      }
  #else
      glutMainLoop();
  #endif
  }
