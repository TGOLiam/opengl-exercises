#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
 
/*
 * Example 19 - Simple Animation with glutIdleFunc
 * ------------------------------------
 * Concept: glutIdleFunc registers a callback that GLUT calls
 * continuously whenever there are no other events to process. This
 * is how classic GLUT programs animate: update a variable, then
 * request a redraw.
 */
 

#include <chrono>
float squareX = -0.8f;
float velocity = 1 * 0.02;
float accel = 20 * 0.02;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.7f, 0.9f);
 
    glBegin(GL_POLYGON);
        glVertex2f(squareX - 0.1f, -0.1f);
        glVertex2f(squareX - 0.1f,  0.1f);
        glVertex2f(squareX + 0.1f,  0.1f);
        glVertex2f(squareX + 0.1f, -0.1f);
    glEnd();
 
    glFlush();
}

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

    if (!timer_passed && current >= accel_timer + std::chrono::seconds(1))
    {
        accel = -(accel); 
        timer_passed = true;
    }
    velocity += accel * dt;
    squareX += velocity * dt;


    if (squareX > 0.7f) {
        squareX = 0.7f;
        
    }
    if (squareX < -0.7f) {
        squareX = -0.7f;
        
    }

    previous = current;

    glutPostRedisplay();
}
 
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Ex19 - Bouncing Square (glutIdleFunc)");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
