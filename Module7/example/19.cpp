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





  // glViewport is usually the same as the window size, but it needs to be
  // updated whenever the window is RESIZED. glutReshapeFunc lets us hook
  // that event and call glViewport with the new dimensions.
  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(0.7f, 0.3f, 0.8f);
      glBegin(GL_TRIANGLES);
          glVertex2f( 0.0f, 0.5f);
          glVertex2f(-0.5f, -0.5f);
          glVertex2f( 0.5f, -0.5f);
      glEnd();
      glFlush();
  }

  void reshape(int width, int height){
      glViewport(0, 0, width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
      glMatrixMode(GL_MODELVIEW);
  }

  int main(int argc, char** argv){
      glutInit(&argc, argv);
      glutInitWindowSize(800, 600);
      glutInitDisplayMode(GLUT_RGBA);
      glutCreateWindow("simple");
      glutDisplayFunc(display);
      glutReshapeFunc(reshape);

  #ifndef __APPLE__
      GLenum err = glewInit();
      if(err == GLEW_OK){
          glutMainLoop();
      }
  #else
      glutMainLoop();
  #endif
  }
