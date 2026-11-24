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

  // Capstone: a two-face color cube (position VBO + color VBO combined via
  // glBufferSubData) that drifts sideways once per second using the
  // lecture's translate() matrix helper, with ESC-key cleanup.
  GLuint VBOid;
  bool ready = false;

  GLfloat cubeVertices[] = {
      // Top - Green
       1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1.0f,
      // Front - Red
       1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f,-1.0f, 1.0f,       1.0f,-1.0f, 1.0f,
  };
  GLfloat cubeColors[] = {
      0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f,
      1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f, 1.0f,0.0f,0.0f,
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

void cube(){
    if(!ready){
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, (24 + 24) * sizeof(GLfloat), NULL,
GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 24 * sizeof(GLfloat), cubeVertices);
        glBufferSubData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), 24 * sizeof(GLfloat),
cubeColors);
        ready = true;
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(24 * sizeof(GLfloat)));
    glDrawArrays(GL_QUADS, 0, 8);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void drift(int value){
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    for(int i = 0; i < 24; i += 3){
        translate(0.02f, 0.0f, 0.0f, i);




    }
    glutPostRedisplay();
    glutTimerFunc(1000, drift, 0);
}

void monitorKeyboard(unsigned char key, int x, int y){
    if(key == 27){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBOid);
        exit(0);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    cube();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if(err == GLEW_OK){
        glutTimerFunc(1000, drift, 0);
        glutMainLoop();
    }
#else
        glutTimerFunc(1000, drift, 0);
    glutMainLoop();
#endif
}
