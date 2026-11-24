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



// Reproduces the lecture's "Combining Transformation" slide: multiplying
// a translation matrix by a scale matrix into ONE combined matrix, then
// applying that single combined matrix to a vertex.
void multiply4x4(const float a[16], const float b[16], float out[16]){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            out[row*4 + col] = 0.0f;
            for(int k = 0; k < 4; k++){
                out[row*4 + col] += a[row*4 + k] * b[k*4 + col];
            }
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

   // Translate by (0.2, 0.1, 0.0)
   float T[16] = {
       1.0f, 0.0f, 0.0f, 0.2f,
       0.0f, 1.0f, 0.0f, 0.1f,
       0.0f, 0.0f, 1.0f, 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f
   };
   // Scale by 1.5 in all directions
   float S[16] = {
       1.5f, 0.0f, 0.0f, 0.0f,
       0.0f, 1.5f, 0.0f, 0.0f,
       0.0f, 0.0f, 1.5f, 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f
   };
   float combined[16];
   multiply4x4(T, S, combined);

   float vx = -0.2f, vy = -0.1f, vz = 0.0f, vw = 1.0f;
   float rx = combined[0]*vx + combined[1]*vy + combined[2]*vz + combined[3]*vw;
   float ry = combined[4]*vx + combined[5]*vy + combined[6]*vz + combined[7]*vw;
   float rz = combined[8]*vx + combined[9]*vy + combined[10]*vz + combined[11]*vw;





         cout << "Result: (" << rx << ", " << ry << ", " << rz << ")" << endl;

         glPointSize(12.0f);
         glBegin(GL_POINTS);
             glColor3f(1.0f, 1.0f, 1.0f);
             glVertex3f(vx, vy, vz);
             glColor3f(1.0f, 0.5f, 0.0f);
             glVertex3f(rx, ry, rz);
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
