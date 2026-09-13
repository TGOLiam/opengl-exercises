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

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    const int sides = 10;
    float radius;

        glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sides; i++) {
        float angle = (float)i / sides * FULL_TURN + QUARTER_TURN; // start
        
        if (i % 2 == 0) radius = 0.8f;
        else radius = 0.4f;
        
        
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
