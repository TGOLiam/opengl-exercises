#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

#include <cmath>
#define PI M_PI
#define FULL_TURN 2.0f*PI
#define QUARTER_TURN FULL_TURN/4.0f

struct Color{
    float r;
    float g;
    float b;
};

struct Position{
    float x;
    float y;
};

void drawQuad(Position base, Color c, float width, float height){
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POLYGON);
    
    glVertex2f(base.x, base.y);
    glVertex2f(base.x, base.y + height);
    glVertex2f(base.x + width, base.y + height);
    glVertex2f(base.x + width, base.y);

    glEnd();
}

void drawStar(Position base, Color c, float size){
    const int sides = 10;
    float radius;

    Position center;
    center.x = base.x + size/2;
    center.y = base.y + size/2;

    glColor3f(c.r, c.g, c.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(center.x, center.y);
    for (int i = 0; i <= sides; i++) {
        float angle = (float)i / sides * FULL_TURN + QUARTER_TURN; // start
        
        if (i % 2 == 0) radius = size/2.0f;
        else radius = size/4.0f;
        
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(center.x + x, center.y + y);
    }
    glEnd();
}

struct FlagColor{
    Color even_stripe;
    Color odd_stripe;
    Color star;
    Color star_background;
};

void drawFlag(
    Position center,
    FlagColor fc, 
    float width, float height, 
    int stripe_count = 6,
    float background_portion = 0.5f
){
    Position base;
    base.x = center.x - width/2;
    base.y = center.y - height/2;

    float stripe_size = height / stripe_count;

    for (int row = 0; row < stripe_count; row++){
        Color row_c;
        if (row % 2 == 0) row_c = fc.even_stripe;
        else row_c = fc.odd_stripe;
        
        drawQuad(
            Position{base.x, base.y + row*stripe_size},
            row_c,
            width,
            stripe_size
        );
    }

    // Star Background
    float background_size = height * background_portion;
    drawQuad(
        Position{base.x, base.y + height - background_size},
        fc.star_background,
        background_size,
        background_size
    );

    // Star
    drawStar(
        Position{base.x, base.y + height - background_size},
        fc.star,
        background_size
    );
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    const int STRIPE_COUNT = 12;
    const float width = 1.0f;
    const float height = 0.5f;

    drawFlag(
        Position{0.0f, 0.0f},
        FlagColor{
            .even_stripe = Color{1.0f, 1.0f, 1.0f},
            .odd_stripe = Color{1.0f, 0.0f, 0.0f},
            .star = Color{1.0f, 1.0f, 0.0f},
            .star_background = Color{0.0f, 0.0f, 1.0f},
        },
        width,
        height,
        STRIPE_COUNT
    );
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    
    glutCreateWindow("PE_20");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
