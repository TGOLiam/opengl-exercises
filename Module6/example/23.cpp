#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>

struct Vec4 {
    float x, y, z, w;
};

// Rotate a homogeneous direction around Z. Its w=0 means any translation
// portion of a transform would not change it; rotation still changes x and y.
Vec4 rotateDirectionZ(Vec4 direction, float degrees) {
    const float radians = degrees * 3.14159265f / 180.0f;
    const float c = cosf(radians);
    const float s = sinf(radians);

    return {
        c * direction.x - s * direction.y,
        s * direction.x + c * direction.y,
        direction.z,
        direction.w
    };
}

// Add a direction (w=0) to a position (w=1), producing another position.
Vec4 addDirection(Vec4 position, Vec4 direction) {
    return {
        position.x + direction.x,
        position.y + direction.y,
        position.z + direction.z,
        position.w
    };
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *text++);
    }
}

void drawAxes() {
    glLineWidth(1.0f);
    glColor3f(0.38f, 0.38f, 0.42f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f( 1.0f, 0.0f);
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f,  1.0f);
    glEnd();
}

void drawSegment(Vec4 start, Vec4 end, float r, float g, float b) {
    glLineWidth(5.0f);
    glColor3f(r, g, b);
    glBegin(GL_LINES);
        glVertex2f(start.x, start.y);
        glVertex2f(end.x, end.y);
    glEnd();

    glPointSize(11.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.85f, 0.2f); // start position
        glVertex2f(start.x, start.y);
        glColor3f(r, g, b);            // end position
        glVertex2f(end.x, end.y);
    glEnd();
}

void setupPanel(int panel, int width, int height) {
    const int panelWidth = width / 2;
    glViewport(panel * panelWidth, 0,
               panel == 1 ? width - panelWidth : panelWidth, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2, 1.2, -1.2, 1.2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    const int width = glutGet(GLUT_WINDOW_WIDTH);
    const int height = glutGet(GLUT_WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);

    // The line is represented as a position plus a direction:
    // start has w=1, while direction has w=0.
    const Vec4 start = {-0.55f, -0.15f, 0.0f, 1.0f};
    const Vec4 direction = {1.0f, 0.35f, 0.0f, 0.0f};
    const Vec4 end = addDirection(start, direction);

    const float angle = 30.0f;
    const Vec4 rotatedDirection = rotateDirectionZ(direction, angle);
    const Vec4 rotatedEnd = addDirection(start, rotatedDirection);

    setupPanel(0, width, height);
    drawAxes();
    drawSegment(start, end, 0.25f, 0.65f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.08f, 1.02f, "Original: position w=1 + direction w=0");
    drawText(-1.08f, 0.88f, "Yellow = start; blue = end");

    setupPanel(1, width, height);
    drawAxes();
    drawSegment(start, rotatedEnd, 1.0f, 0.35f, 0.25f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.08f, 1.02f, "Rotate direction 30 degrees around Z");
    drawText(-1.08f, 0.88f, "Start stays fixed; direction turns");

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 480);
    glutCreateWindow("Module 6 Example 23 - Homogeneous Direction");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
        return 1;
    }
#endif

    glClearColor(0.08f, 0.08f, 0.10f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
