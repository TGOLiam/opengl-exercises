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



  // The pyramid's front and right faces, stored as a single VBO of
  // position data, drawn with GL_TRIANGLES.
  GLfloat pyramidVertices[] = {
       0.0f, 1.0f, 0.0f,
      -1.0f, -1.0f, 1.0f,
       1.0f, -1.0f, 1.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
  };

  void displayObject(){
      GLuint VBOid;
      glGenBuffers(1, &VBOid);
      glBindBuffer(GL_ARRAY_BUFFER, VBOid);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, pyramidVertices,
  GL_STATIC_DRAW);




       glEnableClientState(GL_VERTEX_ARRAY);
       glClear(GL_COLOR_BUFFER_BIT);

       glColor3f(1.0f, 1.0f, 0.0f);
       glVertexPointer(3, GL_FLOAT, 0, 0);
       glDrawArrays(GL_TRIANGLES, 0, 6);

       glDisableClientState(GL_VERTEX_ARRAY);
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
