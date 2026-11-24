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



  // Demonstrates the lecture's Homogeneous Coordinates rule:
  // w == 1 means the vector is a POSITION; w == 0 means a DIRECTION.
  // A translation matrix moves a position but leaves a direction unchanged.
  struct Vec4 { float x, y, z, w; };

  Vec4 applyTranslation(Vec4 v, float tx, float ty, float tz){
      // Only affects x,y,z when w == 1 (position); has no effect when w == 0 (direction)
      Vec4 r;
      r.x = v.x + tx * v.w;
      r.y = v.y + ty * v.w;
      r.z = v.z + tz * v.w;
      r.w = v.w;
      return r;
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);

      Vec4 position = { -0.3f, -0.3f, 0.0f, 1.0f }; // a point in space
      Vec4 direction = { 0.3f, 0.3f, 0.0f, 0.0f }; // a direction vector





      Vec4 movedPosition = applyTranslation(position, 0.3f, 0.0f, 0.0f);
      Vec4 movedDirection = applyTranslation(direction, 0.3f, 0.0f, 0.0f);

      cout << "Position moved from (" << position.x << "," << position.y
           << ") to (" << movedPosition.x << "," << movedPosition.y << ")" << endl;
      cout << "Direction stayed at (" << movedDirection.x << "," << movedDirection.y
           << ") -- unaffected because w == 0" << endl;

      glPointSize(12.0f);
      glBegin(GL_POINTS);
          glColor3f(0.0f, 1.0f, 0.0f);
          glVertex3f(position.x, position.y, 0.0f);
          glColor3f(1.0f, 1.0f, 0.0f);
          glVertex3f(movedPosition.x, movedPosition.y, 0.0f);
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
