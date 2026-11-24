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

// The lecture's full "Converted Program with Matrix Translation" example:
// a hexagon that shifts to the right once per second via translate(),
// stopping and cleaning up its buffer after 10 updates.
void display();
void translate(float x, float y, float z, int startindex);

GLfloat polygonvertices[] = {
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
     1.0f, 0.0f, 0.0f,
     0.5f,-0.5f, 0.0f,
    -0.5f,-0.5f, 0.0f,
    -1.0f, 0.0f, 0.0f
};

GLfloat *mapV = NULL;
int forUpdate = 0;
int ctr = 0;
GLuint VBOid;

void polygon(){
    if(!forUpdate){
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, polygonvertices,
GL_DYNAMIC_DRAW);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_POLYGON, 0, 6);
        glDisableClientState(GL_VERTEX_ARRAY);
    } else {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_POLYGON, 0, 6);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void translate(float x, float y, float z, int startindex){
    GLfloat w = 1.0f;
    GLfloat ta[] = {
        1.0f, 0.0f, 0.0f, x,




         0.0f, 1.0f, 0.0f, y,
         0.0f, 0.0f, 1.0f, z,
         0.0f, 0.0f, 0.0f, 1
    };

    GLfloat tx, ty, tz;
    tx = (ta[0]*mapV[startindex]) + (ta[1]*mapV[startindex+1]) +
(ta[2]*mapV[startindex+2]) + (ta[3]* w);
    ty = (ta[4]*mapV[startindex]) + (ta[5]*mapV[startindex+1]) +
(ta[6]*mapV[startindex+2]) + (ta[7]* w);
    tz = (ta[8]*mapV[startindex]) + (ta[9]*mapV[startindex+1]) +
(ta[10]*mapV[startindex+2]) + (ta[11]* w);

    mapV[startindex] = tx;
    mapV[startindex+1] = ty;
    mapV[startindex+2] = tz;
}

void modifyPolygon(int value){
    if(value == 10){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBOid);
        exit(0);
    }

    forUpdate = 1;

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    mapV = (GLfloat *) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    for(int i = 0; i < 18; i += 3){
        translate(.1f, 0.0f, 0.0f, i);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glutPostRedisplay();

    glutTimerFunc(1000, modifyPolygon, value + 1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(.16f, .72f, .08f, 1.0f);
    polygon();
    glFlush();
    if(!forUpdate){
        glutTimerFunc(1000, modifyPolygon, 0);
    }
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
