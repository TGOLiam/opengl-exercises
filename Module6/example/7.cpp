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

  // Applies a scaling matrix (per the lecture's Scaling slide) to a VBO
  // triangle ONE TIME via glMapBuffer, growing it by 1.5x before drawing.
  GLuint VBOid;
  bool ready = false;
  GLfloat triVertices[] = {
       0.0f, 0.3f, 0.0f,
      -0.3f, -0.3f, 0.0f,
       0.3f, -0.3f, 0.0f,
  };

  // Scaling matrix template, from the lecture's Scaling slide
  void scale(float sx, float sy, float sz, int startindex){
      GLfloat *mapV = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);




    GLfloat sa[] = {
        sx,   0.0f, 0.0f, 0.0f,
        0.0f, sy,   0.0f, 0.0f,
        0.0f, 0.0f, sz,   0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    GLfloat w = 1.0f;

    GLfloat sx_, sy_, sz_;
    sx_ = (sa[0]*mapV[startindex]) + (sa[1]*mapV[startindex+1]) +
(sa[2]*mapV[startindex+2]) + (sa[3]*w);
    sy_ = (sa[4]*mapV[startindex]) + (sa[5]*mapV[startindex+1]) +
(sa[6]*mapV[startindex+2]) + (sa[7]*w);
    sz_ = (sa[8]*mapV[startindex]) + (sa[9]*mapV[startindex+1]) +
(sa[10]*mapV[startindex+2]) + (sa[11]*w);

    mapV[startindex]   = sx_;
    mapV[startindex+1] = sy_;
    mapV[startindex+2] = sz_;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void triangle(){
    if(!ready){
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, triVertices,
GL_DYNAMIC_DRAW);

        for(int i = 0; i < 9; i += 3){
            scale(1.5f, 1.5f, 1.5f, i);
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
    glColor3f(.86f, .32f, .08f);
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
