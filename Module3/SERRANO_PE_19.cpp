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


int score = 0;
const Color colors[3] = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
};

void mouse(int button, int state, int, int){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        score++;
        glutPostRedisplay();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Color square_color = {0.3f, 0.3f, 0.3f};
    if (score >= 5) {
        square_color = colors[(score / 5 - 1) % 3];
    }

    glColor3f(square_color.r, square_color.g, square_color.b);
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.4f);
        glVertex2f(-0.4f, 0.4f);
        glVertex2f(0.4f, 0.4f);
        glVertex2f(0.4f, -0.4f);
    glEnd();

    char score_text[100];

    snprintf(
        score_text,
        sizeof(score_text),
        "Score: %d",
        score
    );

    drawString(
        score_text,
        Position{-0.12f, 0.0f},
        Color{1.0f, 1.0f, 1.0f},
        GLUT_BITMAP_HELVETICA_18
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_19 - HUD Score with Color Milestones");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
