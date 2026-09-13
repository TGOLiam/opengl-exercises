#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>


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


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    const float width = 1.6f;
    const float height = 0.2f;

    drawRect(
        Position{-0.8f, 0.8f},
        Color{1.0f, 0.0f, 0.0f},
        width*0.9,
        height
    );
    
    drawRect(
        Position{-0.8f , 0.8f},
        Color{1.0f, 0.0f, 0.0f},
        height,
        width
    );
    
    drawRect(
        Position{-0.8f, height*0.5},
        Color{1.0f, 0.0f, 0.0f},
        width*0.8,
        height
    );
    
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_13");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
