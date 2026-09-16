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

struct Position{
    float x,y;
};

struct Color{
    int r,g,b;
};

void drawCircle(Position center, float radius, Color c){
    const int sides = 40;

    glColor3ub(c.r, c.g, c.b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(center.x, center.y);

        for(int i = 0; i <= sides; i++){
            float angle = i * FULL_TURN/sides;

            float x = center.x + radius * cosf(angle);
            float y = center.y + radius * sinf(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

void drawBase(Position center, float width, float height, Color c){
    glColor3ub(c.r, c.g, c.b);
    glBegin(GL_QUADS);
        glVertex2f(center.x - width/2, center.y + height/2);
        glVertex2f(center.x + width/2, center.y + height/2);
        glVertex2f(center.x + width/8, center.y - height/2);
        glVertex2f(center.x - width/8, center.y - height/2);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    drawBase(
        Position{0.0f, -0.3f},
        0.6f,
        0.7f,
        Color{139, 69, 19}
    );

    drawCircle(
        Position{0.0f, 0.2f},
        0.35f,
        Color{255, 165, 0}
    );

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_16");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
