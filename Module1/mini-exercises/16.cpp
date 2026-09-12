#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 16 — Regular Pentagon
 *
 * Task: Use sin/cos and GL_LINE_LOOP to draw a six-sided orange regular polygon.
 */
#include <cmath>
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.6f, 0.2f, 0.8f);
    const int sides = 100;
    const float radius = 0.6f;
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; i++) {
        float angle = (float)i / sides * 2.0f * 3.14159265f + 1.5707963f; // start
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex16 - Regular Pentagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}