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





// A pure "by hand" demonstration of the matrix-vector product from
// the lecture's Matrix Vector Product slide: multiplying a 4x4 matrix
// by a (x,y,z,w) vector, printed to the console AND drawn as two points.
struct Vec4 { float x, y, z, w; };

Vec4 matrixVectorProduct(const float m[16], Vec4 v){
    Vec4 r;
    r.x = m[0]*v.x + m[1]*v.y + m[2]*v.z + m[3]*v.w;
    r.y = m[4]*v.x + m[5]*v.y + m[6]*v.z + m[7]*v.w;
    r.z = m[8]*v.x + m[9]*v.y + m[10]*v.z + m[11]*v.w;
    r.w = m[12]*v.x + m[13]*v.y + m[14]*v.z + m[15]*v.w;
    return r;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // A translation matrix that moves a point by (0.4, 0.2, 0.0)
    float m[16] = {
        1.0f, 0.0f, 0.0f, 0.4f,
        0.0f, 1.0f, 0.0f, 0.2f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    Vec4 before = { -0.4f, -0.2f, 0.0f, 1.0f };
    Vec4 after = matrixVectorProduct(m, before);

    cout << "Before: (" << before.x << ", " << before.y << ", " << before.z << ")" <<
endl;
    cout << "After: (" << after.x << ", " << after.y << ", " << after.z << ")" <<
endl;

    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(before.x, before.y, before.z);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(after.x, after.y, after.z);
    glEnd();

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
