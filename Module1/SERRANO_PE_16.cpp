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

Position p = {
    .x = 0.0f,
    .y = 0.0f
};

Color c = {
    .r = 1.0f,
    .g = 0.0f,
    .b = 0.0f
};
const float radius = 0.1f;

void display(){
    glClearColor(0.52f, 0.8f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawCircle(
        p,
        c,
        radius
    );

    glFlush();
}

float x_velocity = 0.5f;
float y_velocity = 0.5f;
bool has_started = false;
std::chrono::steady_clock::time_point previous;
std::chrono::steady_clock::time_point accel_timer;

bool timer_passed = false;
void idle() {
    if (!has_started){
        previous = accel_timer = std::chrono::steady_clock::now();
        has_started = true;
        return;
    }
    auto current = std::chrono::steady_clock::now();

    std::chrono::duration<float> elapsed = current - previous;
    float dt = elapsed.count();

    p.x += x_velocity * dt;
    p.y += y_velocity * dt;

    if (p.y + radius > 1.0f) {
        y_velocity = -y_velocity;
        p.y = 1.0f - radius;
    }
    if (p.y - radius < -1.0f) {
        y_velocity = -y_velocity;
        p.y = -1.0f + radius;
    }

    if (p.x + radius > 1.0f) {
        x_velocity = -x_velocity;
        p.x = 1.0f - radius;
    }
    if (p.x - radius < -1.0f) {
        x_velocity = -x_velocity;
        p.x = -1.0f + radius;
    }

    previous = current;
    glutPostRedisplay();
}

#include <cstdlib>
#include <ctime>


int main(int argc, char** argv){

    std::srand(std::time(nullptr));
    float x_random = (float)std::rand() / RAND_MAX;
    float y_random = (float)std::rand() / RAND_MAX;

    p.x += x_random;
    p.y += y_random;

    if (x_random > 0.5) x_velocity = -x_velocity;
    if (y_random > 0.5) y_velocity = -y_velocity;



    glutInit(&argc, argv);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("PE_16");


    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
