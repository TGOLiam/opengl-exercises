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

void drawSquare(Position center, Color c, float width, float height){
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POLYGON);
    
    Position base_p;

    base_p.x = center.x - width*0.5;
    base_p.y = center.y - height*0.5;

    glVertex2f(base_p.x, base_p.y);
    glVertex2f(base_p.x + width, base_p.y);
    glVertex2f(base_p.x + width, base_p.y + height);
    glVertex2f(base_p.x, base_p.y + height);

    glEnd();
}

Position p = {
    .x = 0.0f,
    .y = 0.0f
};

Color c = {
    .r = 1.0f,
    .g = 0.0f,
    .b = 0.0f
};
const float width = 0.3f;
const float height = width; 

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawSquare(
        p, 
        c,
        width,
        height
    );
    
    glFlush();
}

void keyboard(int key, int x, int y) {
    if (key == GLUT_KEY_UP) p.y += 0.2f;
    if (key == GLUT_KEY_DOWN) p.y -= 0.2f;
    if (key == GLUT_KEY_LEFT) p.x -= 0.2f;
    if (key == GLUT_KEY_RIGHT) p.x += 0.2f;

    if (p.x + width /2  > 0.9f) p.x = 0.9f - width/2;
    if (p.x - width /2 < -0.9f ) p.x = -0.9f + width/2;
    if (p.y + height /2 > 0.9f) p.y = 0.9f - height/2;
    if (p.y - width /2 < -0.9f) p.y = -0.9f + height/2;

    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_15");

    glutSpecialFunc(keyboard);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
