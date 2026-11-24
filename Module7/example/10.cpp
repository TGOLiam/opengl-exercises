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



  // The lecture's exact triangle()/animateTriangle() sample: a VBO
  // triangle set up once, translated/scaled once, then rotated a little
  // more every frame using glPushMatrix()/glPopMatrix() so the rotation
  // doesn't accumulate onto other state.
  bool initTriangle = true;
  float angle = 1.0f;
  GLuint VBOid;

  GLfloat trianglevertices[] = {





      0.0f, .75f, 0.0f,
     -0.75f, 0.0f, 0.0f,
      0.75f, 0.0f, 0.0f
};

void triangle(){
    if(initTriangle){
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, trianglevertices,
GL_STATIC_DRAW);

         glEnableClientState(GL_VERTEX_ARRAY);

         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();

         glTranslatef(0.0f, -0.5f, 0.0f);
         glScalef(.75f, .75f, 0.0f);
         initTriangle = false;
     }

     glPushMatrix();
     glRotatef(angle, 0.0f, 0.0f, 1.0);

     glVertexPointer(3, GL_FLOAT, 0, 0);
     glDrawArrays(GL_TRIANGLES, 0, 3);
     glPopMatrix();
}

void animateTriangle(int value){
    angle++;
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(.16f, .72f, .08f, 1.0f);

     triangle();
     glFlush();

     glutTimerFunc(200, animateTriangle, 1);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA);
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
