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



  // Immediate-mode 4-triangle pyramid: the starting point before we
  // convert this shape to vertex arrays and VBOs in later examples.
  void displayTriangle(){
      glClear(GL_COLOR_BUFFER_BIT);

      glBegin(GL_TRIANGLES);
          // Front
          glColor3f(1.0f, 0.0f, 0.0f);
          glVertex3f( 0.0f, 1.0f, 0.0f);




            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f( 1.0f, -1.0f, 1.0f);

           // Right
           glColor3f(1.0f, 0.0f, 0.0f);
           glVertex3f(0.0f, 1.0f, 0.0f);
           glColor3f(0.0f, 0.0f, 1.0f);
           glVertex3f(1.0f, -1.0f, 1.0f);
           glColor3f(0.0f, 1.0f, 0.0f);
           glVertex3f(1.0f, -1.0f, -1.0f);
       glEnd();

      glFlush();
  }
  void display(){ displayTriangle(); }

  int main(int argc, char** argv){
      glutInit(&argc, argv);
      glutInitWindowSize(800, 600);
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
