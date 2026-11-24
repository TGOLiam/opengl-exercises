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



  // glRotate(angle, x, y, z) rotates an object around a specified axis.
  // This rotates the triangle 45 degrees around the Z axis, a fixed amount.
  void display(){
      glClear(GL_COLOR_BUFFER_BIT);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

       glColor3f(0.2f, 0.5f, 0.9f);
       glBegin(GL_TRIANGLES);
           glVertex2f( 0.0f, 0.5f);
           glVertex2f(-0.5f, -0.5f);
           glVertex2f( 0.5f, -0.5f);
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
