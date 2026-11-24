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



  // glOrtho(left, right, bottom, top, zNear, zFar) sets up an orthographic
  // (parallel) projection -- objects keep their size regardless of depth.
  void init(){




       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
       glMatrixMode(GL_MODELVIEW);
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glLoadIdentity();
      glColor3f(0.3f, 0.7f, 0.4f);
      glBegin(GL_TRIANGLES);
          glVertex2f( 0.0f, 1.0f);
          glVertex2f(-1.0f, -1.0f);
          glVertex2f( 1.0f, -1.0f);
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
