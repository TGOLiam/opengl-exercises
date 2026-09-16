#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    const int quad_count = 5;
    const float quad_width = 1.6f / quad_count;
    const float start_x = -0.8f;
    const float bottom_y = -0.4f;
    const float top_y = 0.4f;

    for(int i = 0; i < quad_count; i++){
        float left_x = start_x + i * quad_width;
        float right_x = left_x + quad_width;

        if(i % 2 == 0){
            glColor3ub(255, 165, 0);
        }
        else{
            glColor3ub(138, 43, 226);
        }

        glBegin(GL_QUAD_STRIP);
            glVertex2f(left_x, bottom_y);
            glVertex2f(left_x, top_y);
            glVertex2f(right_x, bottom_y);
            glVertex2f(right_x, top_y);
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);

    glutCreateWindow("PE_18");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
