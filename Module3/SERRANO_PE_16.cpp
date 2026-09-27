#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


struct Position{
    float x,y;
};


Position cube_p = {0.0f, 0.0f};
const float width = 0.4f;
const float height = 0.4f;
bool dragging = false;

Position getOpenGLPosition(int x, int y){
    const int window_width = glutGet(GLUT_WINDOW_WIDTH);
    const int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    Position p;
    p.x = (2.0f * x / window_width) - 1.0f;
    p.y = 1.0f - (2.0f * y / window_height);

    return p;
}

void mouse(int button, int state, int, int){
    if (button == GLUT_LEFT_BUTTON) {
        dragging = state == GLUT_DOWN;
    }
}

void mouseMotion(int x, int y){
    if (dragging) {
        cube_p = getOpenGLPosition(x, y);
        glutPostRedisplay();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Position p;
    p.x = cube_p.x - width/2;
    p.y = cube_p.y - height/2;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(p.x, p.y);
        glVertex2f(p.x, p.y + height);
        glVertex2f(p.x + width, p.y + height);
        glVertex2f(p.x + width, p.y);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_16 - Click-and-Drag Square");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}
