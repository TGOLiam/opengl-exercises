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



  // The lecture's animateTriangle() pattern: a global angle variable is
  // incremented every timer tick and wraps back to 0 after 360 degrees.
  float angle = 1.0f;

  void animateTriangle(int value){
      if(angle > 360) angle = 0;
      angle++;
      glutPostRedisplay();
      glutTimerFunc(50, animateTriangle, 1);
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glRotatef(angle, 0.0f, 1.0f, 0.0f);

       glColor3f(0.9f, 0.9f, 0.1f);
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
          glutTimerFunc(50, animateTriangle, 1);
          glutMainLoop();
      }
  #else
          glutTimerFunc(50, animateTriangle, 1);
      glutMainLoop();
  #endif
  }
