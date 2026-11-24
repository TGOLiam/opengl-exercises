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



  // GLUT_DEPTH allocates a Z-buffer for hidden surface elimination, and
  // glEnable(GL_DEPTH_TEST) turns depth testing on. This example draws a
  // near quad and a far quad; toggle depth testing with the 'd' key to see
  // the difference in which one appears "in front."
  bool depthOn = true;

  void display(){
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if(depthOn) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0f, 0.0f, -3.0f);

      // Far quad (drawn first, deeper Z)
      glColor3f(0.2f, 0.4f, 0.9f);
      glBegin(GL_QUADS);
          glVertex3f(-0.6f, -0.6f, -1.0f);
          glVertex3f( 0.6f, -0.6f, -1.0f);
          glVertex3f( 0.6f, 0.6f, -1.0f);
          glVertex3f(-0.6f, 0.6f, -1.0f);
      glEnd();




     // Near quad (drawn second, but SHOULD appear on top only if depth test is on)
     glColor3f(0.9f, 0.6f, 0.1f);
     glBegin(GL_QUADS);
         glVertex3f(-0.3f, -0.3f, 0.5f);
         glVertex3f( 0.3f, -0.3f, 0.5f);
         glVertex3f( 0.3f, 0.3f, 0.5f);
         glVertex3f(-0.3f, 0.3f, 0.5f);
     glEnd();

     glFlush();
 }

 void init(){
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(60, 800.0/600.0, 1.0, 10.0);
     glMatrixMode(GL_MODELVIEW);
 }

 void monitorKeyboard(unsigned char key, int x, int y){
     if(key == 'd'){
         depthOn = !depthOn;
         glutPostRedisplay();
     }
 }

 int main(int argc, char** argv){
     glutInit(&argc, argv);
     glutInitWindowSize(800, 600);
     glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
     glutCreateWindow("simple");
     glutDisplayFunc(display);
     glutKeyboardFunc(monitorKeyboard);

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
