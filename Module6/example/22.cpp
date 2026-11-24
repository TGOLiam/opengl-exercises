#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>

struct Point2 {
    float x, y;
};

Point2 rotateZ(Point2 p, float degrees) {
    const float angle = degrees * 3.14159265f / 180.0f;
    const float c = cosf(angle);
    const float s = sinf(angle);

    // Rz(theta) * (x, y, 0, 1)
    return {
        c * p.x - s * p.y,
        s * p.x + c * p.y
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

void drawPoint(Point2 p, float r, float g, float b) {
    glPointSize(12.0f);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
        glVertex2f(p.x, p.y);
    glEnd();
}

void drawLine(Point2 a, Point2 b, float r, float g, float blue) {
    glLineWidth(5.0f);
    glColor3f(r, g, blue);
    glBegin(GL_LINES);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
    glEnd();
    drawPoint(a, 1.0f, 0.85f, 0.2f); // left/start endpoint
    drawPoint(b, r, g, blue);        // right/end endpoint
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

    // Neither endpoint is at the origin, so rotation visibly moves both.
    const Point2 start = {-0.55f, -0.15f};
    const Point2 end   = { 0.45f,  0.20f};
    const float angle = 30.0f; // acute angle
    const Point2 rotatedStart = rotateZ(start, angle);
    const Point2 rotatedEnd   = rotateZ(end, angle);

    setupPanel(0, width, height);
    drawAxes();
    drawLine(start, end, 0.25f, 0.65f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.08f, 1.02f, "Original line (XY plane)");
    drawText(-1.08f, 0.88f, "Yellow = start; blue = end");

    setupPanel(1, width, height);
    drawAxes();
    drawLine(rotatedStart, rotatedEnd, 1.0f, 0.35f, 0.25f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.08f, 1.02f, "After 30-degree rotation around Z");
    drawText(-1.08f, 0.88f, "Both endpoints rotate around origin");

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 480);
    glutCreateWindow("Module 6 Example 22 - Rotate Around Z");

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
