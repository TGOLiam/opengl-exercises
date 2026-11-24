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

  // Two faces of the lecture's color cube, this time using a position VBO
  // PLUS a color VBO (via glBufferSubData) so every vertex has its own color.
  GLfloat cubeVertices[] = {
      // Top face - 4 verts
       1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
      // Front face - 4 verts
       1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,
       1.0f, -1.0f, 1.0f,
  };
  GLfloat cubeColors[] = {
      0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  };

  void displayObject(){
      GLuint VBOid;
      glGenBuffers(1, &VBOid);
      glBindBuffer(GL_ARRAY_BUFFER, VBOid);




      glBufferData(GL_ARRAY_BUFFER, (24 + 24) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
      glBufferSubData(GL_ARRAY_BUFFER, 0, 24 * sizeof(GLfloat), cubeVertices);
      glBufferSubData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), 24 * sizeof(GLfloat),
  cubeColors);

      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);

      glClear(GL_COLOR_BUFFER_BIT);

      glVertexPointer(3, GL_FLOAT, 0, 0);
      glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(24 * sizeof(GLfloat)));

      glDrawArrays(GL_QUADS, 0, 8);

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
