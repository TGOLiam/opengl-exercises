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

  // The full three-visible-face color cube (top, front, right), using
  // ONE VBO with position data followed by color data via glBufferSubData.
  GLfloat cubeVertices[] = {
      // Top - Green
       1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f,
      // Front - Red
       1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f,-1.0f, 1.0f,       1.0f,-1.0f, 1.0f,
      // Right - Magenta
       1.0f, 1.0f, -1.0f,   1.0f, 1.0f, 1.0f,    1.0f,-1.0f, 1.0f,   1.0f,-1.0f,-1.0f,
  };
  GLfloat cubeColors[] = {
      0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f,
      1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,
      1.0f,0.0f,1.0f, 1.0f,0.0f,1.0f, 1.0f,0.0f,1.0f, 1.0f,0.0f,1.0f,
  };

  void displayObject(){
      GLuint VBOid;
      glGenBuffers(1, &VBOid);
      glBindBuffer(GL_ARRAY_BUFFER, VBOid);

       glBufferData(GL_ARRAY_BUFFER, (36 + 36) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
       glBufferSubData(GL_ARRAY_BUFFER, 0, 36 * sizeof(GLfloat), cubeVertices);




      glBufferSubData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), 36 * sizeof(GLfloat),
  cubeColors);

       glEnableClientState(GL_VERTEX_ARRAY);
       glEnableClientState(GL_COLOR_ARRAY);

       glClear(GL_COLOR_BUFFER_BIT);

       glVertexPointer(3, GL_FLOAT, 0, 0);
       glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(36 * sizeof(GLfloat)));
       glDrawArrays(GL_QUADS, 0, 12);

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
