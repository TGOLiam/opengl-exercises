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



  // gluPerspective(fovy, aspect, zNear, zFar) creates a perspective
  // projection matrix -- objects farther from the viewer appear smaller.
  void init(){
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60, 800.0/600.0, 1.0, 10.0);
      glMatrixMode(GL_MODELVIEW);
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glLoadIdentity();
      glTranslatef(0.0f, 0.0f, -4.0f);

       glBegin(GL_TRIANGLES);
           glColor3f(1.0f, 0.0f, 0.0f);




           glVertex3f( 0.0f, 1.0f, 0.0f);
           glColor3f(0.0f, 1.0f, 0.0f);
           glVertex3f(-1.0f, -1.0f, 1.0f);
           glColor3f(0.0f, 0.0f, 1.0f);
           glVertex3f( 1.0f, -1.0f, 1.0f);
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
