#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glPushMatrix();
    glTranslatef(-0.5f, -0.2f, 0.0f);
    glScalef(0.003f, 0.003f, 1.0f);

    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'I');

    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("PE_07 - Stroke Font Practice");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
