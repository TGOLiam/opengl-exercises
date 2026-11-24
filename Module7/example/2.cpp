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



  // glTranslate() moves (translates) an object along the x, y, and z axes.
  // Here it shifts the triangle 0.4 units to the right of its raw coordinates.
  void display(){
      glClear(GL_COLOR_BUFFER_BIT);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       glTranslatef(0.4f, 0.0f, 0.0f);

       glColor3f(0.9f, 0.4f, 0.1f);
       glBegin(GL_TRIANGLES);
           glVertex2f( 0.0f, 0.3f);
           glVertex2f(-0.3f, -0.3f);
           glVertex2f( 0.3f, -0.3f);
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
