#include<GL/glut.h>
#include<math.h>

const float PI = 3.14159f;

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0;i<num_segments; i++) {
        float theta = 2.0f*PI*float(i)/float(num_segments);
        float x = r*cosf(theta);
        float y = r*sinf(theta);
        glVertex2f(x+cx, y+cy);
    }
    glEnd();
}

void drawDot(float x, float y, float size) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.f, 0.0f);

    float R_big = 0.7f;
    drawCircle(0.0f, 0.0f, R_big, 100);
    drawDot(0.0f, 0.0f, 6.0f);

    float R_small = 0.15f;
    float D = R_big - R_small;

    float smallCenters[4][2]={
        {0.0f, D},
        {0.0f, -D},
        {-D, 0.0f},
        {D, 0.0f}
    };

    for (int i=0; i<4; i++) {
        drawCircle(smallCenters[i][0], smallCenters[i][1], R_small, 50);
        drawDot(smallCenters[i][0], smallCenters[i][1], 6.0f);
    }

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char**argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Circle Pattern");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}