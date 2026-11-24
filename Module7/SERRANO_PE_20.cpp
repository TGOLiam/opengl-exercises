#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <cstdlib>
#include <iostream>

GLuint baseVBO = 0;
float baseAngle = 0.0f;
float jointAngle = 0.0f;
GLfloat positions[] = {
  -0.8f, -0.7f, -0.8f,  0.8f, -0.7f, -0.8f,
   0.8f, -0.7f,  0.8f, -0.8f, -0.7f,  0.8f
};
GLfloat colors[] = {
  0.2f, 0.7f, 1.0f,  0.3f, 0.9f, 0.7f,
  0.2f, 0.5f, 1.0f,  0.4f, 0.8f, 1.0f
};

#ifndef __APPLE__
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  (void)source; (void)id; (void)severity; (void)length; (void)userParam;
  if (type == GL_DEBUG_TYPE_ERROR)
    std::cerr << "OpenGL error: " << message << std::endl;
}
#endif

void buildBase() {
  glGenBuffers(1, &baseVBO);
  glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawBase() {
  glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glColorPointer(3, GL_FLOAT, 0, (void *)sizeof(positions));
  glBegin(GL_QUADS);
  for (int i = 0; i < 4; i++) glArrayElement(i);
  glEnd();
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawArm() {
  glPushMatrix();
  glTranslatef(0.0f, -0.7f, 0.0f);
  glRotatef(baseAngle, 0.0f, 1.0f, 0.0f);
  glColor3f(1.0f, 0.5f, 0.2f);
  glPushMatrix();
  glTranslatef(0.0f, 0.45f, 0.0f);
  glScalef(0.24f, 0.9f, 0.24f);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, 0.9f, 0.0f);
  glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);
  glColor3f(1.0f, 0.9f, 0.3f);
  glPushMatrix();
  glTranslatef(0.0f, 0.35f, 0.0f);
  glScalef(0.18f, 0.7f, 0.18f);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(3.0, 2.0, 5.0, 0.0, 0.1, 0.0, 0.0, 1.0, 0.0);
  drawBase();
  drawArm();
  glFlush();
}

void animateArm(int value) {
  (void)value;
  baseAngle += 2.0f;
  jointAngle += 3.0f;
  if (baseAngle >= 360.0f) baseAngle = 0.0f;
  if (jointAngle >= 360.0f) jointAngle = 0.0f;
  glutPostRedisplay();
  glutTimerFunc(30, animateArm, 0);
}

void monitorKeyboard(unsigned char key, int x, int y) {
  (void)x; (void)y;
  if (key == 27) {
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &baseVBO);
    exit(0);
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
#ifndef __APPLE__
  glutInitContextFlags(GLUT_DEBUG);
#endif
  glutCreateWindow("PE_20 - Color VBO Base and Arm");
  glutDisplayFunc(display);
  glutKeyboardFunc(monitorKeyboard);
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
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 10.0);
  buildBase();
  glutTimerFunc(30, animateArm, 0);
  glutMainLoop();
  return 0;
}
