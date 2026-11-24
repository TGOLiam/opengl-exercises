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



  // A hierarchical model: a base quad, and an "arm" quad attached to it.
  // Rotating the base rotates the arm too, but glPushMatrix()/glPopMatrix()
  // let us give the arm its OWN additional local rotation on top of that.
  float baseAngle = 20.0f;
  float armAngle = 40.0f;

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

       glPushMatrix();
           glTranslatef(0.0f, -0.4f, 0.0f);
           glRotatef(baseAngle, 0.0f, 0.0f, 1.0f);

            // Base segment
            glColor3f(0.3f, 0.6f, 0.9f);
            glBegin(GL_QUADS);
                glVertex2f(-0.1f, 0.0f);
                glVertex2f( 0.1f, 0.0f);
                glVertex2f( 0.1f, 0.5f);
                glVertex2f(-0.1f, 0.5f);
            glEnd();

            // Arm segment: inherits the base's transform, PLUS its own extra rotation
            glPushMatrix();
                glTranslatef(0.0f, 0.5f, 0.0f);
                glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
                glColor3f(0.9f, 0.4f, 0.2f);
                glBegin(GL_QUADS);




                   glVertex2f(-0.08f, 0.0f);
                   glVertex2f( 0.08f, 0.0f);
                   glVertex2f( 0.08f, 0.4f);
                   glVertex2f(-0.08f, 0.4f);
               glEnd();
           glPopMatrix();
       glPopMatrix();

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
