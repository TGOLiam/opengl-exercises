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


Position object_p = {0.0f, 0.0f};
int mouse_x = 0;
int mouse_y = 0;

float square_size = 0.3f;
float pulse_speed = 0.2f;
const float min_size = 0.3f;
const float max_size = 0.5f;

Position getOpenGLPosition(int x, int y){
    const int window_width = glutGet(GLUT_WINDOW_WIDTH);
    const int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    Position p;
    p.x = (2.0f * x / window_width) - 1.0f;
    p.y = 1.0f - (2.0f * y / window_height);

    return p;
}

void mouse(int, int state, int x, int y){
    if (state == GLUT_DOWN) {
        object_p = getOpenGLPosition(x, y);
        glutPostRedisplay();
    }
}

void mouseMotion(int x, int y){
    object_p = getOpenGLPosition(x, y);
    glutPostRedisplay();
}

void passiveMotion(int x, int y){
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}

void idle(){
    static int previousTime = glutGet(GLUT_ELAPSED_TIME);
    const int currentTime = glutGet(GLUT_ELAPSED_TIME);
    const float deltaTime = (currentTime - previousTime) / 1000.0f;

    previousTime = currentTime;

    square_size += pulse_speed * deltaTime;

    if (square_size >= max_size) {
        square_size = max_size;
        pulse_speed = -pulse_speed;
    }
    if (square_size <= min_size) {
        square_size = min_size;
        pulse_speed = -pulse_speed;
    }

    glutPostRedisplay();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Position p;
    p.x = object_p.x - square_size/2;
    p.y = object_p.y - square_size/2;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(p.x, p.y);
        glVertex2f(p.x, p.y + square_size);
        glVertex2f(p.x + square_size, p.y + square_size);
        glVertex2f(p.x + square_size, p.y);
    glEnd();

    drawString(
        "Pulsing square",
        Position{object_p.x + square_size/2 + 0.03f, object_p.y},
        Color{1.0f, 1.0f, 1.0f},
        GLUT_BITMAP_HELVETICA_18
    );

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
        Position{-0.9f, 0.9f},
        Color{1.0f, 1.0f, 1.0f},
        GLUT_BITMAP_HELVETICA_18
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_20 - Interactive Text Placer");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(passiveMotion);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
