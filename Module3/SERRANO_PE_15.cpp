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


int seconds = 30;

void timer(int){
    seconds--;

    glutPostRedisplay();

    if (seconds > 0) {
        glutTimerFunc(1000, timer, 0);
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (seconds > 0) {
        char countdown[100];

        snprintf(
            countdown,
            sizeof(countdown),
            "Time remaining: %d",
            seconds
        );

        drawString(
            countdown,
            Position{-0.3f, 0.0f},
            Color{1.0f, 1.0f, 1.0f},
            GLUT_BITMAP_HELVETICA_18
        );
    }
    else {
        drawString(
            "Time's up!",
            Position{-0.15f, 0.0f},
            Color{1.0f, 0.0f, 0.0f},
            GLUT_BITMAP_HELVETICA_18
        );
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_15 - 30-Second Countdown Timer");

    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
