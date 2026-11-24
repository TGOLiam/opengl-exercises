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

// Applies the lecture's translate() matrix function to a VBO triangle
// ONE TIME using glMapBuffer, moving it 0.3 units in X before drawing.
GLuint VBOid;
bool ready = false;
GLfloat triVertices[] = {
     0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};

// Translation matrix template, from the lecture's Matrix Translation slide
void translate(float x, float y, float z, int startindex){
    GLfloat *mapV = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    GLfloat w = 1.0f;
    GLfloat ta[] = {
        1.0f, 0.0f, 0.0f, x,
        0.0f, 1.0f, 0.0f, y,
        0.0f, 0.0f, 1.0f, z,
        0.0f, 0.0f, 0.0f, 1
    };

    GLfloat tx, ty, tz;
    tx = (ta[0]*mapV[startindex]) + (ta[1]*mapV[startindex+1]) +
(ta[2]*mapV[startindex+2]) + (ta[3]*w);
    ty = (ta[4]*mapV[startindex]) + (ta[5]*mapV[startindex+1]) +
(ta[6]*mapV[startindex+2]) + (ta[7]*w);
    tz = (ta[8]*mapV[startindex]) + (ta[9]*mapV[startindex+1]) +
(ta[10]*mapV[startindex+2]) + (ta[11]*w);

    mapV[startindex]   = tx;
    mapV[startindex+1] = ty;
    mapV[startindex+2] = tz;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void triangle(){
    if(!ready){
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, triVertices,
GL_DYNAMIC_DRAW);

       for(int i = 0; i < 9; i += 3){





               translate(0.3f, 0.0f, 0.0f, i);
           }
           ready = true;
       } else {
           glBindBuffer(GL_ARRAY_BUFFER, VBOid);
       }

       glEnableClientState(GL_VERTEX_ARRAY);
       glVertexPointer(3, GL_FLOAT, 0, 0);
       glDrawArrays(GL_TRIANGLES, 0, 3);
       glDisableClientState(GL_VERTEX_ARRAY);
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(.16f, .72f, .08f);
      triangle();
      glFlush();
  }

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
