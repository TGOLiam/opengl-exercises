#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct Position{
    float x,y;
};

const float speed = 1.0f;

Position cube_p = {0.0f, 0.0f};
const float width = 0.5f;
const float height = 0.5f;
int moveDirection = 0;

void keyboardDown(unsigned char key, int, int) {
    if (key == 'a' || key == 'A')
        moveDirection = -1;
    else if (key == 'd' || key == 'D')
        moveDirection = 1;
}

void keyboardUp(unsigned char key, int, int) {
    if ((key == 'a' || key == 'A') && moveDirection == -1)
        moveDirection = 0;
    else if ((key == 'd' || key == 'D') && moveDirection == 1)
        moveDirection = 0;
}

void idle() {
    static int previousTime = glutGet(GLUT_ELAPSED_TIME);
    const int currentTime = glutGet(GLUT_ELAPSED_TIME);
    const float deltaTime = (currentTime - previousTime) / 1000.0f;

    previousTime = currentTime;

    if (moveDirection != 0) {
        cube_p.x += moveDirection * speed * deltaTime;
    }

    if (cube_p.x + width/2 >= 0.9f) cube_p.x = 0.9f - width/2;
    if (cube_p.x - width/2 <= -0.9f) cube_p.x = -0.9f + width/2;
    if (cube_p.y + height/2 >= 0.9f) cube_p.y = 0.9f - height/2;
    if (cube_p.y - height/2 <= -0.9f) cube_p.y = -0.9f + height/2;

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
    glutCreateWindow("PE_08 - Clamped Keyboard Movement");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
