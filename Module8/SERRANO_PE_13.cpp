#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cstdio>
#include <cstdlib>



GLuint makeCheckerTexture() {
  unsigned char pixels[64 * 64 * 3];
  for (int y = 0; y < 64; ++y) {
    for (int x = 0; x < 64; ++x) {
      bool light = ((x / 8) + (y / 8)) % 2 == 0;
      int index = (y * 64 + x) * 3;
      pixels[index] = light ? 238 : 35;
      pixels[index + 1] = light ? 210 : 75;
      pixels[index + 2] = light ? 155 : 120;
    }
  }
  GLuint id = 0;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
  return id;
}

void drawQuad(float left, float right, float bottom, float top, float repeat = 1.0f) {
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(left, bottom, 0.0f);
  glTexCoord2f(repeat, 0.0f); glVertex3f(right, bottom, 0.0f);
  glTexCoord2f(repeat, repeat); glVertex3f(right, top, 0.0f);
  glTexCoord2f(0.0f, repeat); glVertex3f(left, top, 0.0f);
  glEnd();
}

void drawText(float x, float y, const char *label) {
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glColor3f(0.95f, 0.95f, 1.0f);
  glRasterPos3f(x, y, 0.1f);
  for (const char *p = label; *p; ++p) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);
}



GLuint textureId = 0;
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glDisable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glColor3f(1.0f, 1.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, textureId);
  drawQuad(-1.8f, 1.8f, -1.8f, 1.8f);
  drawText(-1.0f, -2.1f, "Procedural RGB checkerboard");
  glutSwapBuffers();
}

void closeTexture() {
  glDeleteTextures(1, &textureId);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("PE_13 - Checkerboard Quad");
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glClearColor(0.08f, 0.09f, 0.13f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
  textureId = makeCheckerTexture();
  glutDisplayFunc(display);
  std::atexit(closeTexture);
  glutMainLoop();
  return 0;
}
