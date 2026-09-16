#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>

#define PI M_PI
#define FULL_TURN 2.0f*PI

const int SEGMENT_COUNT = 60;

void setRainbowColor(float t){
    float r = 0.5f + 0.5f * sinf(FULL_TURN * t);
    float g = 0.5f + 0.5f * sinf(FULL_TURN * t + FULL_TURN/3);
    float b = 0.5f + 0.5f * sinf(FULL_TURN * t + 2*FULL_TURN/3);

    glColor3f(r, g, b);
}

void drawRainbowFan(float radius){
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.0f, 0.0f);

        for(int i = 0; i <= SEGMENT_COUNT; i++){
            float t = (float)i / SEGMENT_COUNT;
            float angle = t * FULL_TURN;

            setRainbowColor(t);
            glVertex2f(radius * cosf(angle), radius * sinf(angle));
        }
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    drawRainbowFan(0.8f);

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);

    glutCreateWindow("PE_20");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
