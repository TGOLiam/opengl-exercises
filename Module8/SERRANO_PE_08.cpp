#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cstdio>
#include <cstdlib>


void setMaterial(float red, float green, float blue, float shininess = 24.0f) {
  const GLfloat ambient[] = {red * 0.25f, green * 0.25f, blue * 0.25f, 1.0f};
  const GLfloat diffuse[] = {red, green, blue, 1.0f};
  const GLfloat specular[] = {0.9f, 0.9f, 0.9f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}

void drawSphere(float x, float y, float z, float radius = 0.7f) {
  glPushMatrix();
  glTranslatef(x, y, z);
  glutSolidSphere(radius, 48, 32);
  glPopMatrix();
}

void drawText(float x, float y, const char *label) {
  glDisable(GL_LIGHTING);
  glColor3f(0.94f, 0.95f, 1.0f);
  glRasterPos3f(x, y, 0.0f);
  for (const char *p = label; *p; ++p) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
  glEnable(GL_LIGHTING);
}

float lightX = 1.5f;
float lightY = 2.0f;
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 1.5, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  const GLfloat position[] = {lightX, lightY, 3.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  setMaterial(0.25f, 0.65f, 0.95f, 70.0f);
  drawSphere(0.0f, 0.0f, 0.0f, 1.3f);
  char message[80];
  std::snprintf(message, sizeof(message), "Light x %.1f  y %.1f - arrow keys", lightX, lightY);
  drawText(-1.65f, -1.7f, message);
  glutSwapBuffers();
}
void monitorArrows(int key, int, int) {
  if (key == GLUT_KEY_LEFT) lightX -= 0.3f;
  else if (key == GLUT_KEY_RIGHT) lightX += 0.3f;
  else if (key == GLUT_KEY_DOWN) lightY -= 0.3f;
  else if (key == GLUT_KEY_UP) lightY += 0.3f;
  else return;
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("PE_08 - Move Light With Arrows");
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glClearColor(0.08f, 0.09f, 0.13f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  const GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
  glutDisplayFunc(display);
  glutSpecialFunc(monitorArrows);
  glutMainLoop();
  return 0;
}
