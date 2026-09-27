#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>


struct Position{
    float x,y;
};

struct Color{
    float r,g,b;
};

void drawString(const char *str, Position base, Color c, void *font){
    glColor3f(c.r, c.g, c.b);
    glRasterPos2f(base.x, base.y);

    for (const char *c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


int seconds = 0;
bool running = false;

void mouse(int button, int state, int, int){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            running = true;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            running = false;
        }
    }

    glutPostRedisplay();
}

void timer(int){
    if (running) {
        seconds++;
        glutPostRedisplay();
    }

    glutTimerFunc(1000, timer, 0);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    char stopwatch[100];

    snprintf(
        stopwatch,
        sizeof(stopwatch),
        "Elapsed time: %d seconds",
        seconds
    );

    drawString(
        stopwatch,
        Position{-0.35f, 0.0f},
        running ? Color{0.0f, 1.0f, 0.0f} : Color{1.0f, 0.0f, 0.0f},
        GLUT_BITMAP_HELVETICA_18
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_17 - Mouse-Controlled Stopwatch");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
