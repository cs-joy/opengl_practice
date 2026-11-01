#include<GL/glut.h>
#include<iostream>

void drawLine() {
    int x1=100, y1=100, x2=400, y2=300;
    // int x1=20, y1=30, x2=10, y2=10;

    int dx=x2-x1;
    int dy=y2-y1;

    int p=2*dy-dx;

    int x=x1;
    int y=y1;

    glBegin(GL_POINTS);

    while (x<=x2) {
        glVertex2i(x,y);

        x=x+1;

        if(p<0){
            p=p+2*dy;
        }else{
            y=y+1;
            p=p+2*dy-2*dx;
        }
    }

    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    drawLine();
    glFlush();
}

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
