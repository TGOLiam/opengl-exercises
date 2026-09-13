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
#define QUARTER_TURN FULL_TURN/4.0f


void drawCircleOutline(float ra, float r, float g, float b){
    glColor3f(r, g, b);
    glLineWidth(5.0f);

    const int sides = 60;
    float radius = ra;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sides; i++) {
        float angle = (float)i / sides * FULL_TURN + QUARTER_TURN; // start
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawCircleOutline(0.8f, 1.0f, 0.0f, 0.0f);
    drawCircleOutline(0.4f, 0.0f, 0.0f, 1.0f);
    drawCircleOutline(0.2f, 0.0f, 1.0f, 0.0f);

    
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_11");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
