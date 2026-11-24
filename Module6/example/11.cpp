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

// Uses glBufferData to reserve space for BOTH position and color data,
// then glBufferSubData to upload each block separately -- the pattern
// from the lecture's "glArrayElement(), glColorPointer() and
// glBufferSubData()" slide.
GLfloat triVertices[] = {
     0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};
GLfloat triColors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

void displayObject(){
    GLuint VBOid;
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    // Reserve space for 9 position floats + 9 color floats
    glBufferData(GL_ARRAY_BUFFER, (9 + 9) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triVertices);
    glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), 9 * sizeof(GLfloat),
triColors);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glClear(GL_COLOR_BUFFER_BIT);

   glVertexPointer(3, GL_FLOAT, 0, 0);
   glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(9 * sizeof(GLfloat)));

   glBegin(GL_TRIANGLES);
       glArrayElement(0);
       glArrayElement(1);
       glArrayElement(2);
   glEnd();

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);





      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glDeleteBuffers(1, &VBOid);

      glFlush();
  }
  void display(){ displayObject(); }

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
