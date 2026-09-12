#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
 * Exercise 01 — Empty GLUT Window
 *
 * Task: Make a 480x320 window that clears to a dark teal color; draw no geometry.
 */

#define W_WIDTH 480
#define W_HEIGHT 320

void display(){
    glClearColor(0.0f, 0.201f, 0.205f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

int main(int argc,char**argv){

    glutInit(&argc, argv);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);

    glutCreateWindow("Exercise 01");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
