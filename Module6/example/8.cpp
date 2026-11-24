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

  // Applies the lecture's Rz(theta) rotation matrix to a VBO triangle,
  // once per second via glutTimerFunc, spinning it around the Z axis.
  GLuint VBOid;
  bool ready = false;
  GLfloat triVertices[] = {
       0.0f, 0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
  };

  // Rz(theta) rotation matrix template, from the lecture's Rotation slide




void rotateZ(float degrees, int startindex){
    GLfloat *mapV = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    float rad = degrees * 3.14159265f / 180.0f;
    GLfloat c = cosf(rad), s = sinf(rad);
    GLfloat ra[] = {
        c,   -s,   0.0f, 0.0f,
        s,    c,   0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    GLfloat w = 1.0f;

    GLfloat rx, ry, rz;
    rx = (ra[0]*mapV[startindex]) + (ra[1]*mapV[startindex+1]) +
(ra[2]*mapV[startindex+2]) + (ra[3]*w);
    ry = (ra[4]*mapV[startindex]) + (ra[5]*mapV[startindex+1]) +
(ra[6]*mapV[startindex+2]) + (ra[7]*w);
    rz = (ra[8]*mapV[startindex]) + (ra[9]*mapV[startindex+1]) +
(ra[10]*mapV[startindex+2]) + (ra[11]*w);

    mapV[startindex]   = rx;
    mapV[startindex+1] = ry;
    mapV[startindex+2] = rz;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void triangle(){
    if(!ready){
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, triVertices,
GL_DYNAMIC_DRAW);
        ready = true;
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void spin(int value){
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    for(int i = 0; i < 9; i += 3){
        rotateZ(15.0f, i);
    }
    glutPostRedisplay();
    glutTimerFunc(1000, spin, 0);




  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(.08f, .32f, .86f);
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
          glutTimerFunc(1000, spin, 0);
          glutMainLoop();
      }
  #else
          glutTimerFunc(1000, spin, 0);
      glutMainLoop();
  #endif
  }
