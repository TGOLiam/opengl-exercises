#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cmath>

// Demonstrates why an X-axis line can look like a dot after a 90-degree
// rotation around Y when viewed along Z, while remaining a line in depth.
// Left: original line in the XY view.
// Center: rotated line in the same XY view (the endpoints overlap).
// Right: rotated line from the XZ view, where its depth is visible.
struct Point3 {
    float x, y, z;
};

Point3 rotateY90(Point3 p) {
    const float angle = 90.0f * 3.14159265f / 180.0f;
    const float c = cosf(angle);
    const float s = sinf(angle);

    // Ry(theta) * (x, y, z, 1)
    return {
        c * p.x + s * p.z,
        p.y,
        -s * p.x + c * p.z
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
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_LINES);
        glVertex2f(-1.1f, 0.0f);
        glVertex2f( 1.1f, 0.0f);
        glVertex2f(0.0f, -1.1f);
        glVertex2f(0.0f,  1.1f);
    glEnd();
}

// Select which two coordinates are displayed in this panel.
void projectPoint(Point3 p, int view, float& horizontal, float& vertical) {
    if (view == 0) {          // XY view: looking along Z
        horizontal = p.x;
        vertical = p.y;
    } else {                  // XZ view: looking along Y
        horizontal = p.x;
        vertical = p.z;
    }
}

void drawLine(Point3 a, Point3 b, int view, float r, float g, float blue) {
    float ax, ay, bx, by;
    projectPoint(a, view, ax, ay);
    projectPoint(b, view, bx, by);

    glLineWidth(5.0f);
    glColor3f(r, g, blue);
    glBegin(GL_LINES);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
    glEnd();

    // Mark both endpoints. In the collapsed XY projection these overlap,
    // producing one visible dot.
    glPointSize(12.0f);
    glBegin(GL_POINTS);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
    glEnd();
}

void drawPanel(int panel, const char* title, Point3 a, Point3 b,
               int view, float r, float g, float blue) {
    const int width = glutGet(GLUT_WINDOW_WIDTH);
    const int height = glutGet(GLUT_WINDOW_HEIGHT);
    const int panelWidth = width / 3;

    glViewport(panel * panelWidth, 0,
               panel == 2 ? width - 2 * panelWidth : panelWidth, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.25, 1.25, -1.25, 1.25, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawAxes();
    drawLine(a, b, view, r, g, blue);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-1.15f, 1.05f, title);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    const Point3 start = {0.0f, 0.0f, 0.0f};
    const Point3 end   = {1.0f, 0.0f, 0.0f};
    const Point3 rotatedStart = rotateY90(start);
    const Point3 rotatedEnd   = rotateY90(end);

    drawPanel(0, "Original line: XY view", start, end, 0,
              0.2f, 0.65f, 1.0f);
    drawPanel(1, "After Ry(90): XY view", rotatedStart, rotatedEnd, 0,
              1.0f, 0.35f, 0.2f);
    drawPanel(2, "After Ry(90): XZ view", rotatedStart, rotatedEnd, 1,
              0.2f, 1.0f, 0.45f);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1050, 420);
    glutCreateWindow("Module 6 Example 21 - Y Rotation and View Direction");

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
