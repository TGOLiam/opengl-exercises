#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 17 — Circle Triangle Fan
 *
 * Task: Use GL_TRIANGLE_FAN to make a 48-segment cyan disk centered at (-0.3, 0.2).
 */
#include "common.h"
#include <cmath>



void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    const int segments = 48;
    const float radius = 0.6f;

    glColor3f(0.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
        float center_x = -0.3f;
        float center_y = 0.2f;

        glVertex2f(center_x, center_y);
        for (int i = 0; i <= segments; i++){
            float angle = (float)i/ segments * FULL_TURN + QUARTER_TURN;
            float x = (radius * cosf(angle)) + center_x;
            float y = (radius * sinf(angle)) + center_y;
            glVertex2f(x,y);
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex17 - Circle via Triangle Fan");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}