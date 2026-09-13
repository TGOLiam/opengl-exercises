#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

#include <cmath>
#include <chrono>
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

void drawClockBody(Position base_p, Color c, float r){
    glColor3f(c.r, c.g, c.b);

    const int sides = 60;
    float radius = r;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sides; i++) {
        float angle = (float)i / sides * FULL_TURN + QUARTER_TURN;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(base_p.x + x, base_p.y+y);
    }
    glEnd();
}

const int tick_counts = 60;
const float tick_width = 0.2f;
const float tick_height = 0.2f;
const float clock_radius = 1.0f;

Position tick_pos[tick_counts];

const float angle_step = FULL_TURN / tick_counts;
const float start_angle = QUARTER_TURN;

//start at top

float second_hand_angle;


void display(){
    glClearColor(1.0f, 1.0f, 1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawClockBody(
        Position{0.0f, 0.0f},
        Color{0.0f, 0.0f, 0.0f},
        clock_radius
    );

    glColor3f(0.22f,0.22f,0.22f);
    glPointSize(8.0f);

    for (int i = 0; i < tick_counts; i++){   
        if (i % 5 == 0) glPointSize(8.0f);
        else glPointSize(4.0f);

        

        glBegin(GL_POINTS);
        glVertex2f(tick_pos[i].x, tick_pos[i].y);
        glEnd();
    }

    float hand_length= clock_radius*0.95;

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);

    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(hand_length*cosf(second_hand_angle), hand_length*sinf(second_hand_angle));
    glEnd();


    glFlush();
}

std::time_t prev_timestamp = -1;
void idle() {
    std::time_t timestamp = std::time(nullptr);

    if (timestamp == prev_timestamp) return;

    prev_timestamp = timestamp;

    int seconds = timestamp % 60;

    second_hand_angle = start_angle
        - seconds * (FULL_TURN / 60.0f);

    glutPostRedisplay();
}
int main(int argc, char** argv){
    for (int i = 0; i < tick_counts; i++){
        float angle = start_angle - i * angle_step;
        float x = (clock_radius*0.95) * cosf(angle);
        float y = (clock_radius*0.95) * sinf(angle);
        tick_pos[i].x = x;
        tick_pos[i].y = y;
    }

    glutInit(&argc, argv);

    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("PE_18");
    glutDisplayFunc(display);
    glutIdleFunc(idle);


    glutMainLoop();

    return 0;
}
