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

/* 
 
*/

struct Color{
    float r;
    float g;
    float b;
};

struct Position{
    float x;
    float y;
};

// Defaults to pointing Right
void drawArrow(Position center, Color c, float width, float height){
    Position base;
    base.x = center.x - width/2;
    base.y = center.y - height/2;

    glColor3f(c.r, c.g, c.b);
    // Shaft
    glLineWidth(width*0.3*300);
    glBegin(GL_LINES);
    glVertex2f(base.x, base.y + height/2);
    glVertex2f(base.x + width*0.7, base.y + height/2);
    glEnd();

    base.x = base.x + width*0.7;

    glBegin(GL_TRIANGLES);
        glVertex2f(base.x, base.y);
        glVertex2f(base.x, base.y + height);
        glVertex2f(base.x + width*0.3, base.y + height/2);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    float width = 0.5f;
    float height = 0.3f;

    drawArrow(
        Position{0.0f, 0.0f},
        Color{1.0f, 1.0f, 0.0f},
        width,
        height
    );

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_12");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
