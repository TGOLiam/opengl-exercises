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

struct Color{
    float r;
    float g;
    float b;
};

struct Position{
    float x;
    float y;
};

void drawRect(Position base_p, Color c, float width, float height){
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POLYGON);
    
    glVertex2f(base_p.x, base_p.y);
    glVertex2f(base_p.x + width, base_p.y);
    glVertex2f(base_p.x + width, base_p.y - height);
    glVertex2f(base_p.x, base_p.y - height);

    glEnd();
}

void drawCircle(Position base_p, Color c, float r){
    glColor3f(c.r, c.g, c.b);

    const int sides = 60;
    float radius = r;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(base_p.x, base_p.y);
    for (int i = 0; i <= sides; i++) {
        float angle = (float)i / sides * FULL_TURN + QUARTER_TURN; // start
        float x = radius * cosf(angle) * 0.5f;
        float y = radius * sinf(angle);
        glVertex2f(base_p.x + x, base_p.y+y);
    }
    glEnd();
}


void display(){
    glClearColor(0.52f, 0.8f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawCircle(
        Position{0.0f, 0.067f},
        Color{1.0f, 1.0f, 0.0f},
        0.3f
    );

    drawRect(
        Position{-1.0f, 0.0f}, 
        Color{0.48f, 0.98f, 0.0f},
        2.0f,
        1.0f
    );
    
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100,100);
    glutCreateWindow("PE_14");


    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
