#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


struct Color{
    float r,g,b;
};

Color bg_color = {0.2f, 0.2f, 0.2f};

void mouseEntry(int state){
    if (state == GLUT_ENTERED) {
        bg_color = {0.8f, 0.8f, 0.8f};
    }
    else if (state == GLUT_LEFT) {
        bg_color = {0.2f, 0.2f, 0.2f};
    }

    glutPostRedisplay();
}


void display() {
    glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_11 - Entry-Driven Background");

    glutDisplayFunc(display);
    glutEntryFunc(mouseEntry);
    glutMainLoop();
    return 0;
}
