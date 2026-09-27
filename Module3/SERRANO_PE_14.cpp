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
const float speed = 0.1f;
const float width = 0.4f;
const float height = 0.4f;

void keyboard(unsigned char key, int, int){
    if (key == 'w' || key == 'W') {
        cube_p.y += speed;
    }
    else if (key == 's' || key == 'S') {
        cube_p.y -= speed;
    }

    glutPostRedisplay();
}

void mouse(int, int state, int, int){
    if (state == GLUT_DOWN) {
        cube_p = {0.0f, 0.0f};
    }

    glutPostRedisplay();
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
    glutCreateWindow("PE_14 - Keyboard + Mouse Combo");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
