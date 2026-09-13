#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    float cell_x_base = -1.0f;
    float cell_y_base = 1.0f;
    
    const float cell_width = 0.5f;
    const float cell_height = 0.5f;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++){
            glBegin(GL_POLYGON);

            if ((row+col) % 2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
            else glColor3f(1.0f, 1.0f, 1.0f);

            glVertex2f(cell_x_base, cell_y_base);
            glVertex2f(cell_x_base + cell_width, cell_y_base);
            glVertex2f(cell_x_base + cell_width, cell_y_base - cell_height);
            glVertex2f(cell_x_base, cell_y_base - cell_height);
            glEnd();

            cell_x_base += cell_width;        
        }
        cell_x_base = -1.0f; // reset back

        cell_y_base -= cell_height;
    }
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_09");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
