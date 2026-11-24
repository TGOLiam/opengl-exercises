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



  // The full lecture sample program: a color pyramid (6 vertex "sides",
  // each 3 verts x 4 faces = 12 total), position + color combined into
  // ONE VBO via glBufferSubData, drawn with a glArrayElement() loop,
  // rotated continuously with gluPerspective + gluLookAt set up in init().
  GLuint VBOid;
  bool initTriangle = true;
  float angle = 1.0f;

  GLfloat vertices[] = {
      //------------------- Triangle (4 faces of a pyramid)
       0.0f, 1.0f, 0.0f,
      -1.0f,-1.0f, 1.0f,
       1.0f,-1.0f, 1.0f,





     0.0f, 1.0f, 0.0f,
     1.0f,-1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,

      0.0f, 1.0f, 0.0f,
      1.0f,-1.0f,-1.0f,
     -1.0f,-1.0f,-1.0f,

      0.0f, 1.0f, 0.0f,
     -1.0f,-1.0f,-1.0f,
     -1.0f,-1.0f, 1.0f,
};

GLfloat colorstriangle[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,

     1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 1.0f, 0.0f,

     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,

     1.0f,0.0f,0.0f,
     0.0f,0.0f,1.0f,
     0.0f,1.0f,0.0f,
};

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 800.0/600.0, 1.0, 10.0);
}

void displayTriangle(){
    if(initTriangle){
        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);

        glBufferData(GL_ARRAY_BUFFER, ((9*4) + (9*4)) * sizeof(GLfloat), vertices,
GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, (9*4) * sizeof(GLfloat), (9*4) *
sizeof(GLfloat), colorstriangle);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);





        glVertexPointer(3, GL_FLOAT, 0, 0);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET((9*4)*sizeof(GLfloat)));

        initTriangle = false;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,4.0, 0.0,0.0,0.0, 0.0,1.0,0.0);

    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); // Displaying four sides
        for(int i = 0; i < 12; i++){
            glArrayElement(i);
        }
    glEnd();

    glFlush();
    glPopMatrix();
}

void animateTriangle(int value){
    if(angle > 360) angle = 0;
    angle++;
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    displayTriangle();
    glutTimerFunc(50, animateTriangle, 1);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("simple");
    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if(err == GLEW_OK){
        init();
        glutMainLoop();
    }
#else
        init();
    glutMainLoop();





  #endif
  }
