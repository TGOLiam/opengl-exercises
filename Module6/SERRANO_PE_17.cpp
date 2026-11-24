#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif
#include <cmath>
#include <cstdlib>
#include <iostream>

#ifndef __APPLE__
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar *message, const void *userParam) {
  (void)source; (void)id; (void)length; (void)userParam;
  std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "GL ERROR " : "")
            << "type = " << type << ", severity = " << severity << ", message = " << message << std::endl;
}
#endif

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.2f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLES);
  glVertex2f(-0.5f, -0.5f); glVertex2f(0.5f, -0.5f); glVertex2f(0.0f, 0.5f);
  glEnd();
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  #ifndef __APPLE__
  glutInitContextFlags(GLUT_DEBUG);
#endif
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_17 - OpenGL Debug Callback");
  glutDisplayFunc(display);
  
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif
  #ifndef __APPLE__
  if (!GLEW_VERSION_4_3 && !GLEW_KHR_debug) {
    std::cerr << "OpenGL debug output is not supported by this context." << std::endl;
    return 1;
  }
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(messageCallback, 0);
  glEnable((GLenum)0xFFFFFFFF);
#else
  std::cerr << "OpenGL debug callbacks are not available through Apple OpenGL headers." << std::endl;
#endif
  glutMainLoop();
  return 0;
}
