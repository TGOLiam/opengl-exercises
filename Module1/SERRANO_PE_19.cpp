#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

struct Color{
    float r;
    float g;
    float b;
};

Color preset_colors[6] = {
    {1.0f, 0.0f, 0.0f},  // Red
    {0.0f, 1.0f, 0.0f},  // Green
    {0.0f, 0.0f, 1.0f},  // Blue
    {1.0f, 1.0f, 0.0f},  // Yellow
    {1.0f, 0.0f, 1.0f},  // Magenta
    {0.0f, 1.0f, 1.0f}   // Cyan
};

std::string preset_colors_names[6] = {
    "Red",
    "Green",
    "Blue",
    "Yellow",
    "Magenta",
    "Cyan"
};
int current_preset = 0;

void display(){
    Color c = preset_colors[current_preset];
    glClearColor(c.r, c.g, c.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
    
    int num = key - '0';
    if (num >= 1 && num <= 6) {
        current_preset = num-1;
        std::cout <<  "Background: " << preset_colors_names[current_preset] << std::endl;
    } else return;
    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("PE_19");


    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
