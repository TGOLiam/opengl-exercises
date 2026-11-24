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





// glPushMatrix()/glPopMatrix() save and restore the current transformation
// matrix, so a transformation applied to ONE shape doesn't leak into the next.
void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Shape 1: rotated, inside a push/pop pair
    glPushMatrix();
        glTranslatef(-0.4f, 0.0f, 0.0f);
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glColor3f(0.9f, 0.3f, 0.1f);
        glBegin(GL_QUADS);
            glVertex2f(-0.2f, -0.2f);
            glVertex2f( 0.2f, -0.2f);
            glVertex2f( 0.2f, 0.2f);
            glVertex2f(-0.2f, 0.2f);
        glEnd();
    glPopMatrix();

    // Shape 2: NOT rotated -- the matrix was restored by glPopMatrix()
    glTranslatef(0.4f, 0.0f, 0.0f);
    glColor3f(0.1f, 0.5f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f, 0.2f);
        glVertex2f(-0.2f, 0.2f);
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
