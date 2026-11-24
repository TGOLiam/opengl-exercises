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



  // glViewport(x, y, width, height) defines the drawable region of the
  // window. This example splits an 800x600 window into two side-by-side
  // viewports, each drawing the SAME triangle.
  void drawTriangle(){
      glColor3f(0.4f, 0.8f, 0.3f);
      glBegin(GL_TRIANGLES);
          glVertex2f( 0.0f, 0.5f);
          glVertex2f(-0.5f, -0.5f);
          glVertex2f( 0.5f, -0.5f);
      glEnd();
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);

       // Left half of the window
       glViewport(0, 0, 400, 600);





       drawTriangle();

       // Right half of the window
       glViewport(400, 0, 400, 600);
       drawTriangle();

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
