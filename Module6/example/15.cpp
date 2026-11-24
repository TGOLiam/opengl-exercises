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

// Uses glArrayElement() inside glBegin/glEnd with a FOR LOOP instead of
// hand-typing each call, per the lecture's comment: "you can just create
// a loop for all the vertices."
GLfloat hexVertices[] = {
    -0.5f, 0.25f, 0.0f,
     0.0f, 0.5f, 0.0f,
     0.5f, 0.25f, 0.0f,
     0.5f,-0.25f, 0.0f,
     0.0f,-0.5f, 0.0f,
    -0.5f,-0.25f, 0.0f,
};
GLfloat hexColors[] = {
    1.0f,0.0f,0.0f, 1.0f,0.5f,0.0f, 1.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f, 0.0f,0.0f,1.0f, 0.6f,0.0f,1.0f,
};

void displayObject(){
    GLuint VBOid;
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBufferData(GL_ARRAY_BUFFER, (18 + 18) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 18 * sizeof(GLfloat), hexVertices);
    glBufferSubData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), 18 * sizeof(GLfloat),
hexColors);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glClear(GL_COLOR_BUFFER_BIT);

    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(18 * sizeof(GLfloat)));

    glBegin(GL_POLYGON);
        for(int i = 0; i < 6; i++){
            glArrayElement(i);
        }
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
