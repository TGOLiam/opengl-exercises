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
#define HALF_TURN PI
#define QUARTER_TURN FULL_TURN/4.0f

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    const int sides = 7;
    const float radius = 0.8f;

    glColor3ub(255, 165, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    float angle_step = HALF_TURN/sides;
    for (int i = 0; i <= sides; i++) {
        float angle = i*angle_step ; // start
            
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_10");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
