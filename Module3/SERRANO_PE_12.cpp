#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


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


Position label_p = {-0.8f, 0.0f};
float speed = 0.5f;

void idle(){
    static int previousTime = glutGet(GLUT_ELAPSED_TIME);
    const int currentTime = glutGet(GLUT_ELAPSED_TIME);
    const float deltaTime = (currentTime - previousTime) / 1000.0f;

    previousTime = currentTime;

    label_p.x += speed * deltaTime;

    if (label_p.x >= 0.55f) {
        label_p.x = 0.55f;
        speed = -speed;
    }
    if (label_p.x <= -0.8f) {
        label_p.x = -0.8f;
        speed = -speed;
    }

    glutPostRedisplay();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawString(
        "Bouncing label",
        label_p,
        Color{1.0f, 1.0f, 1.0f},
        GLUT_BITMAP_HELVETICA_18
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_12 - Idle-Driven Bouncing Label");

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
