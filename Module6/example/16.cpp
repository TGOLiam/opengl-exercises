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



  // The lecture's error-handling pattern: register a GL_DEBUG_OUTPUT
  // callback so any OpenGL error prints a message instead of failing silently.
  void GLAPIENTRY MessageCallback(GLenum source,
                                   GLenum type,
                                   GLuint id,
                                   GLenum severity,
                                   GLsizei length,
                                   const GLchar* message,
                                   const void* userParam){
      fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",




                 (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
                 type, severity, message);
  }

  void display(){
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(1.0f, 1.0f, 1.0f);
      glBegin(GL_TRIANGLES);
          glVertex2f(-0.5f, -0.5f);
          glVertex2f( 0.5f, -0.5f);
          glVertex2f( 0.0f, 0.5f);
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
          glEnable(GL_DEBUG_OUTPUT);
          glDebugMessageCallback(MessageCallback, 0);
          printf("OpenGL version supported by this platform (%s): \n",
  glGetString(GL_VERSION));
          printf("OpenGL vendor (%s): \n", glGetString(GL_VENDOR));
          glutMainLoop();
      }
  #else
          glEnable(GL_DEBUG_OUTPUT);
          glDebugMessageCallback(MessageCallback, 0);
          printf("OpenGL version supported by this platform (%s): \n",
  glGetString(GL_VERSION));
          printf("OpenGL vendor (%s): \n", glGetString(GL_VENDOR));
      glutMainLoop();
  #endif
  }
