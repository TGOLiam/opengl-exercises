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

int mouse_x = 0;
int mouse_y = 0;

void mouse(int x, int y){
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    char coordinates[100];

    snprintf(
        coordinates,
        sizeof(coordinates),
        "Mouse: (%d, %d)",
        mouse_x,
        mouse_y
    );


    drawString(
        coordinates,
        Position{-0.3f, 0.0f},
        Color{1.0f, 1.0f, 1.0f},
        GLUT_BITMAP_HELVETICA_18
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_10 - Passive Motion Pixel Readout");

    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouse);
    glutMainLoop();
    return 0;
}
