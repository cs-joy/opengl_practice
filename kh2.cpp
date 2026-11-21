#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Original
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(0,1);
    glEnd();

    // Translation
    glPushMatrix();
    glTranslatef(2,0,0);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(0,1);
    glEnd();
    glPopMatrix();

    // Rotation
    glPushMatrix();
    glTranslatef(4,0,0);
    glRotatef(45,0,0,1);
    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(0,1);
    glEnd();
    glPopMatrix();

    // Scaling
    glPushMatrix();
    glTranslatef(6,0,0);
    glScalef(1.5,1.5,1);
    glColor3f(1,0,1);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1,0);
    glVertex2f(1,1);
    glVertex2f(0,1);
    glEnd();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700,400);
    glutCreateWindow("Quadrilateral Transformation");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,8,-2,3);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}