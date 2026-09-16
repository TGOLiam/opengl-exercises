#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

struct Position{
    float x,y;
};

struct Color{
    int r,g,b;
};

void drawStipple(Position start, Position end, Color c, int repeat_factor, GLushort pattern){
    const float width = 5.0f;

    glColor3ub(c.r, c.g, c.b);
    glLineWidth(width);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(repeat_factor, pattern);

    glBegin(GL_LINES);
        glVertex2f(start.x, start.y);
        glVertex2f(end.x, end.y);
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    GLushort dash_pattern = 0x00FF;
    GLushort dot_pattern = 0xAAAA;

    drawStipple(
        Position{-0.5, 0.5},
        Position{0.5, 0.5},
        Color{255, 0, 0},
        1,
        dash_pattern
    );
    
    drawStipple(
        Position{-0.5, -0.5},
        Position{0.5, -0.5},
        Color{255, 0, 0},
        2,
        dot_pattern
    );
    
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_14");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
