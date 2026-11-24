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




  // glFrustum(left, right, bottom, top, zNear, zFar) manually defines the
  // viewing frustum, offering more control than gluPerspective.
  void init(){
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
      glMatrixMode(GL_MODELVIEW);
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glLoadIdentity();
      glTranslatef(0.0f, 0.0f, -3.0f);

         glColor3f(0.6f, 0.3f, 0.9f);
         glBegin(GL_QUADS);
             glVertex3f(-0.5f, -0.5f, 0.0f);
             glVertex3f( 0.5f, -0.5f, 0.0f);
             glVertex3f( 0.5f, 0.5f, 0.0f);
             glVertex3f(-0.5f, 0.5f, 0.0f);
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
