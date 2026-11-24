#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cstdio>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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


GLuint loadWoodTexture() {
  const char *paths[] = {"Module8/assets/woodtexture.jpg", "assets/woodtexture.jpg", "woodtexture.jpg"};
  unsigned char *pixels = nullptr;
  int width = 0, height = 0, channels = 0;
  stbi_set_flip_vertically_on_load(1);
  for (const char *path : paths) {
    pixels = stbi_load(path, &width, &height, &channels, 3);
    if (pixels) break;
  }
  if (!pixels) {
    std::fprintf(stderr, "Could not load woodtexture.jpg: %s. Using checkerboard fallback.\n", stbi_failure_reason());
    return makeCheckerTexture();
  }
  GLuint id = 0;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
  stbi_image_free(pixels);
  return id;
}


void drawTexturedCube(float size) {
  const GLfloat corners[6][4][3] = {
    {{-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}, {-1, 1, 1}},
    {{ 1,-1,-1}, {-1,-1,-1}, {-1, 1,-1}, { 1, 1,-1}},
    {{-1,-1,-1}, {-1,-1, 1}, {-1, 1, 1}, {-1, 1,-1}},
    {{ 1,-1, 1}, { 1,-1,-1}, { 1, 1,-1}, { 1, 1, 1}},
    {{-1, 1, 1}, { 1, 1, 1}, { 1, 1,-1}, {-1, 1,-1}},
    {{-1,-1,-1}, { 1,-1,-1}, { 1,-1, 1}, {-1,-1, 1}}
  };
  const GLfloat normals[6][3] = {
    {0,0,1}, {0,0,-1}, {-1,0,0}, {1,0,0}, {0,1,0}, {0,-1,0}
  };
  const GLfloat uv[4][2] = {{0,0}, {1,0}, {1,1}, {0,1}};
  glBegin(GL_QUADS);
  for (int face = 0; face < 6; ++face) {
    glNormal3fv(normals[face]);
    for (int vertex = 0; vertex < 4; ++vertex) {
      glTexCoord2fv(uv[vertex]);
      glVertex3f(corners[face][vertex][0] * size,
                 corners[face][vertex][1] * size,
                 corners[face][vertex][2] * size);
    }
  }
  glEnd();
}

GLuint textureId = 0;
float angle = 0.0f;
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glDisable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glColor3f(1.0f, 1.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glPushMatrix();
  glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  drawTexturedCube(1.25f);
  glPopMatrix();
  drawText(-1.3f, -2.0f, "Image mapped to six faces");
  glutSwapBuffers();
}
void rotateCube(int) {
  angle += 1.5f;
  if (angle >= 360.0f) angle = 0.0f;
  glutPostRedisplay();
  glutTimerFunc(30, rotateCube, 0);
}

void closeTexture() {
  glDeleteTextures(1, &textureId);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("PE_15 - Textured Rotating Cube");
#ifndef __APPLE__
  if (glewInit() != GLEW_OK) return 1;
#endif
  glClearColor(0.08f, 0.09f, 0.13f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);
  textureId = loadWoodTexture();
  glutDisplayFunc(display);
  glutTimerFunc(30, rotateCube, 0);
  std::atexit(closeTexture);
  glutMainLoop();
  return 0;
}
