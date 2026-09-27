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


Position mouse_p = {0.0f, 0.0f};

void mouseMotion(int x, int y){
    const int window_width = glutGet(GLUT_WINDOW_WIDTH);
    const int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    mouse_p.x = (2.0f * x / window_width) - 1.0f;
    mouse_p.y = 1.0f - (2.0f * y / window_height);

    glutPostRedisplay();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    char coordinates[100];

    snprintf(
        coordinates,
        sizeof(coordinates),
        "OpenGL: (%.2f, %.2f)",
        mouse_p.x,
        mouse_p.y
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
    glutCreateWindow("PE_09 - Active Motion Coordinate Display");

    glutDisplayFunc(display);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}
