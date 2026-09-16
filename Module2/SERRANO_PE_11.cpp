#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

struct Position
{
    float x, y;
};


void drawQuad(Position center, float width, float height){

    Position base;
    base.x = center.x - width/2;
    base.y = center.y - height/2;

    glVertex2f(base.x, base.y);
    glVertex2f(base.x, base.y + height);
    glVertex2f(base.x + width, base.y + height);
    glVertex2f(base.x + width, base.y);

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.65f, 0.0f);
        drawQuad(
            Position{-0.3f, 0.0f},
            0.5f,
            0.5f
        );

        glColor3f(1.0f, 0.0f, 0.0f);
        drawQuad(
            Position{0.3f, 0.0f},
            0.5f,
            0.5f
        );
    glEnd();

    
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
