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
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(base_p.x + x, base_p.y+y);
    }
    glEnd();
}

const float brightness = 0.5f;
int TRAFFIC_STATE = 0;
Color traffic_state_c[3] = {
    {1.0f, 0.0f, 0.0f},
    {0.5f, 0.5f, 0.0f},
    {0.0f, 0.5f, 0.0f}
};

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    const float width = 0.8f;
    const float height = 1.7f;

    Position p = {
        .x = -0.4f, 
        .y = 0.8f
    };

    drawRect(
        p, 
        Color{0.66f, 0.66f, 0.66f},
        width,
        height
    ); 

    int j = 0;
    for (float i = 0.25f; i <= 0.75f; i += 0.25f){
        drawCircle(
            Position{p.x + width/2, p.y - height*i},
            traffic_state_c[j],
            0.2f
        );

        j++;
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'n' || key == 'N') TRAFFIC_STATE = (TRAFFIC_STATE +1)%3;
    else return;    
    
    switch (TRAFFIC_STATE){
        case 0:
            if (traffic_state_c[2].g == 1.0f) {
                traffic_state_c[2].g -= brightness;
            }
            traffic_state_c[0].r += brightness;
            break;
        case 1:
            if (traffic_state_c[0].r == 1.0f) {
                traffic_state_c[0].r -= brightness;
            }
            traffic_state_c[1].r += brightness;
            traffic_state_c[1].g += brightness;

            break;
        case 2:
            if (traffic_state_c[1].r == 1.0f &&
                traffic_state_c[1].g == 1.0f) {
                traffic_state_c[1].r -= brightness;
                traffic_state_c[1].g -= brightness;
            }
            traffic_state_c[2].g += brightness;
            break;

    }
    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("PE_17");


    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
