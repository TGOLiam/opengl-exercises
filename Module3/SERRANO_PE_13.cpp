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


int counter = 0;

void timer(int){
    counter++;

    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    char count[100];

    snprintf(
        count,
        sizeof(count),
        "Counter: %d",
        counter
    );

    drawString(
        count,
        Position{-0.2f, 0.0f},
        Color{1.0f, 1.0f, 1.0f},
        GLUT_BITMAP_HELVETICA_18
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_13 - Timer-Driven Counter");

    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
