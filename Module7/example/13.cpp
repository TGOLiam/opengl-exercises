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



  // gluLookAt(eyeX,eyeY,eyeZ, centerX,centerY,centerZ, upX,upY,upZ) defines
  // a viewing transformation -- where the "camera" is and what it looks at.
  void init(){
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60, 800.0/600.0, 1.0, 10.0);
      glMatrixMode(GL_MODELVIEW);
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glLoadIdentity();

      // eye at (0,0,4), looking at the origin, with +Y as "up"
      gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

      glColor3f(0.9f, 0.6f, 0.1f);
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
