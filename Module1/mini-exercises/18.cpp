#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 18 — Keyboard Input
 *
 * Task: Add a keyboard callback where 1, 2, and 3 select red, green, and blue for a circle.
 */
#include "common.h"
#include <cmath>


struct Circle{
    float r;
    float g;
    float b;
};

Circle c = {
    .r = 1.0f,
    .g = 0.0f,
    .b = 0.0f
};

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    const int segments = 48;
    const float radius = 0.6f;

    glColor3f(c.r, c.g, c.b);

    glBegin(GL_TRIANGLE_FAN);
        float center_x = 0.0f;
        float center_y = 0.0f;
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

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'r':
            c.r = 1.0f;
            c.g = 0.0f;
            c.b = 0.0f;
            break;
        
        case 'g':
            c.r = 0.0f;
            c.g = 1.0f;
            c.b = 0.0f;
            break;
        
        case 'b':
            c.r = 0.0f;
            c.g = 0.0f;
            c.b = 1.0f;
            break;
        
        case 27:
            exit(0);            
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercise 18");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}