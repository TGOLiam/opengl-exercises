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
float speed = 0.5f;
bool mouse_inside = false;

void mouseEntry(int state){
    mouse_inside = state == GLUT_ENTERED;
}

void idle(){
    static int previousTime = glutGet(GLUT_ELAPSED_TIME);
    const int currentTime = glutGet(GLUT_ELAPSED_TIME);
    const float deltaTime = (currentTime - previousTime) / 1000.0f;

    previousTime = currentTime;

    if (mouse_inside) {
        cube_p.x += speed * deltaTime;

        if (cube_p.x + width/2 >= 0.9f) {
            cube_p.x = 0.9f - width/2;
            speed = -speed;
        }
        if (cube_p.x - width/2 <= -0.9f) {
            cube_p.x = -0.9f + width/2;
            speed = -speed;
        }

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
    glutCreateWindow("PE_18 - Mouse-Activated Square Animation");

    glutDisplayFunc(display);
    glutEntryFunc(mouseEntry);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
