#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <iostream>

#ifndef __APPLE__
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  (void)source; (void)id; (void)severity; (void)length; (void)userParam;
  if (type == GL_DEBUG_TYPE_ERROR)
    std::cerr << "OpenGL error: " << message << std::endl;
}
#endif

void setupProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
#ifndef __APPLE__
  glEnable((GLenum)0xFFFFFFFF);  // Deliberately invalid: reported by the callback.
#endif
  gluPerspective(60.0, 1.0, 1.0, 10.0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -3.0f);
  glColor3f(0.3f, 0.8f, 0.5f);
  glutSolidCube(1.2);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
#ifndef __APPLE__
  glutInitContextFlags(GLUT_DEBUG);
#endif
  glutCreateWindow("PE_17 - Intentional Debug Error");
  glutDisplayFunc(display);
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glEnable(GL_DEPTH_TEST);
#ifndef __APPLE__
  if (GLEW_VERSION_4_3 || GLEW_KHR_debug) {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(messageCallback, 0);
  } else {
    std::cerr << "Debug output is unavailable in this OpenGL context.\n";
  }
#endif
  setupProjection();
  glutMainLoop();
  return 0;
}
