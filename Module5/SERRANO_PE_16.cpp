#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>

#define PI M_PI
#define FULL_TURN 2.0f * PI

const int SUN_SEGMENTS = 24;

GLuint sunVBO;
GLuint groundVBO;
GLuint groundIndexVBO;
GLuint treeVBO;

void buildSun() {
  GLfloat sun[(SUN_SEGMENTS + 2) * 2];
  const float center_x = 0.55f;
  const float center_y = 0.55f;
  const float radius = 0.18f;
  const float angle_step = FULL_TURN / SUN_SEGMENTS;

  sun[0] = center_x;
  sun[1] = center_y;
  for (int i = 0; i <= SUN_SEGMENTS; i++) {
    float angle = i * angle_step;
    int offset = (i + 1) * 2;
    sun[offset] = center_x + radius * cosf(angle);
    sun[offset + 1] = center_y + radius * sinf(angle);
  }

  glGenBuffers(1, &sunVBO);
  glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(sun), sun, GL_STATIC_DRAW);
}

void buildGround() {
  GLfloat ground[] = {
    -1.0f, -0.55f,
     1.0f, -0.55f,
     1.0f, -1.0f,
    -1.0f, -1.0f,
  };
  GLubyte indices[] = {0, 1, 2, 0, 2, 3};

  glGenBuffers(1, &groundVBO);
  glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STATIC_DRAW);

  glGenBuffers(1, &groundIndexVBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void buildTree() {
  GLfloat tree[] = {
     0.0f,  0.35f,
    -0.25f, -0.55f,
     0.25f, -0.55f,
  };

  glGenBuffers(1, &treeVBO);
  glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
  glVertexPointer(2, GL_FLOAT, 0, 0);
  glColor3ub(255, 200, 40);
  glDrawArrays(GL_TRIANGLE_FAN, 0, SUN_SEGMENTS + 2);

  glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
  glVertexPointer(2, GL_FLOAT, 0, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
  glColor3ub(70, 160, 70);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

  glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
  glVertexPointer(2, GL_FLOAT, 0, 0);
  glColor3ub(40, 120, 60);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600);
  glutCreateWindow("PE_16 - Three-Shape VBO Scene");
  glutDisplayFunc(display);

#ifndef __APPLE__
  if (glewInit() != GLEW_OK) {
    return 1;
  }
#endif

  buildSun();
  buildGround();
  buildTree();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glutMainLoop();
  return 0;
}
