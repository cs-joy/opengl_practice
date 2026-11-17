// #include <GL/glut.h>

// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT);

//     glColor3f(0.0, 0.0, 0.0);
//     glLineWidth(2.0);

//     // Triangle 1
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(120, 180);
//         glVertex2f(165, 330);
//         glVertex2f(220, 195);
//     glEnd();

//     // Triangle 2
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(300, 210);
//         glVertex2f(355, 350);
//         glVertex2f(400, 220);
//     glEnd();

//     // Triangle 3 (Right-facing)
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(470, 180);
//         glVertex2f(470, 300);
//         glVertex2f(550, 240);
//     glEnd();

//     // Triangle 4 (Large right-facing)
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(630, 120);
//         glVertex2f(630, 370);
//         glVertex2f(770, 245);
//     glEnd();

//     glFlush();
// }

// void init()
// {
//     glClearColor(1.0, 1.0, 1.0, 1.0);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluOrtho2D(0, 800, 0, 500);
// }

// int main(int argc, char** argv)
// {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(800, 500);
//     glutInitWindowPosition(100, 100);

//     glutCreateWindow("Four Triangles");

//     init();
//     glutDisplayFunc(display);

//     glutMainLoop();

//     return 0;
// }

// #include <GL/glut.h>

// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT);

//     glColor3f(0.0, 0.0, 0.0);
//     glLineWidth(3.0);

//     // Triangle 1 - Improved Symmetrical Triangle
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(100, 180);
//         glVertex2f(160, 340);
//         glVertex2f(220, 180);
//     glEnd();

//     // Triangle 2 - Improved Symmetrical Triangle
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(280, 180);
//         glVertex2f(340, 340);
//         glVertex2f(400, 180);
//     glEnd();

//     // Triangle 3 - Right Facing Triangle
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(470, 180);
//         glVertex2f(470, 300);
//         glVertex2f(560, 240);
//     glEnd();

//     // Triangle 4 - Large Right Facing Triangle
//     glBegin(GL_LINE_LOOP);
//         glVertex2f(630, 120);
//         glVertex2f(630, 370);
//         glVertex2f(780, 245);
//     glEnd();

//     glFlush();
// }

// void init()
// {
//     glClearColor(1.0, 1.0, 1.0, 1.0);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();

//     gluOrtho2D(0, 800, 0, 500);
// }

// int main(int argc, char** argv)
// {
//     glutInit(&argc, argv);

//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(800, 500);
//     glutInitWindowPosition(100, 100);

//     glutCreateWindow("Four Beautiful Triangles");

//     init();

//     glutDisplayFunc(display);

//     glutMainLoop();

//     return 0;
// }

#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,0.0,0.0);
    glLineWidth(3.0);

    glBegin(GL_LINE_LOOP);
        glVertex2f(110,190);
        glVertex2f(160,300);
        glVertex2f(210,190);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(290,190);
        glVertex2f(340,300);
        glVertex2f(390,190);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(470,180);
        glVertex2f(470,300);
        glVertex2f(560,240);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(630,120);
        glVertex2f(630,370);
        glVertex2f(780,245);
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,500);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Four Beautiful Triangles");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}