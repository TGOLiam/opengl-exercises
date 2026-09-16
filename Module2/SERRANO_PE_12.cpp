#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

struct Position
{
    float x, y;
};

/* 
Objective: Practice the alternating bottom/top vertex order required by GL_QUAD_STRIP.
Task: Use GL_QUAD_STRIP to build a 'staircase' ribbon made of at least 3 connected quads of increasing
height.
Hints:
• Remember: vertices alternate bottom, top, bottom, top as you move across the strip (NOT outline
order).
• Increase the 'top' Y coordinate for each successive pair to create a rising staircase look
*/


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(255, 165, 0);
  
    const int strip_count = 3;
    const float strip_width = 1.5f / strip_count;
    const float bottom_y = -0.8f;

    glBegin(GL_QUAD_STRIP);

    const float start_x = -0.8f;

    for (int i = 0; i <= strip_count; i++) {
        float x = start_x + i * strip_width;
        float top_y = bottom_y + 0.3f + i * 0.3f;

        glVertex2f(x, bottom_y); 
        glVertex2f(x, top_y);  
    }

    glEnd();
    
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_12");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
