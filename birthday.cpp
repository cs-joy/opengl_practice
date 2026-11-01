#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const float PI = 3.14159f;
float time_val = 0.0f;

struct Confetti {
    float x, y;
    float speedY;
    float rotation;
    float color[3];
};
const int NUM_CONFETTI = 100;
Confetti confetti[NUM_CONFETTI];

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawText(float x, float y, const char* string, void* font) {
    glRasterPos2f(x, y);
    int len = (int)strlen(string);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

void initConfetti() {
    for (int i = 0; i < NUM_CONFETTI; i++) {
        confetti[i].x = (rand() % 1000) - 500.0f;
        confetti[i].y = (rand() % 1000) - 500.0f;
        confetti[i].speedY = (rand() % 10 + 5) / 10.0f;
        confetti[i].rotation = rand() % 360;
        confetti[i].color[0] = (rand() % 100) / 100.0f;
        confetti[i].color[1] = (rand() % 100) / 100.0f;
        confetti[i].color[2] = (rand() % 100) / 100.0f;
    }
}

void timer(int value) {
    time_val += 0.05f;
    
    for (int i = 0; i < NUM_CONFETTI; i++) {
        confetti[i].y -= confetti[i].speedY;
        confetti[i].rotation += 2.0f;
        
        if (confetti[i].y < -500) {
            confetti[i].y = 500;
            confetti[i].x = (rand() % 1000) - 500.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < NUM_CONFETTI; i++) {
        glPushMatrix();
        glTranslatef(confetti[i].x, confetti[i].y, 0.0f);
        glRotatef(confetti[i].rotation, 0.0f, 0.0f, 1.0f);
        glColor3fv(confetti[i].color);
        glBegin(GL_QUADS);
        glVertex2f(-5.0f, -5.0f);
        glVertex2f(5.0f, -5.0f);
        glVertex2f(5.0f, 5.0f);
        glVertex2f(-5.0f, 5.0f);
        glEnd();
        glPopMatrix();
    }

    float bob1 = sinf(time_val) * 15.0f;
    float bob2 = cosf(time_val) * 15.0f;

    glColor3f(1.0f, 0.3f, 0.3f);
    drawCircle(-300.0f, 200.0f + bob1, 40.0f, 50);
    glBegin(GL_LINES);
    glVertex2f(-300.0f, 160.0f + bob1);
    glVertex2f(-300.0f, 50.0f);
    glEnd();

    glColor3f(0.3f, 0.5f, 1.0f);
    drawCircle(300.0f, 250.0f + bob2, 45.0f, 50);
    glBegin(GL_LINES);
    glVertex2f(300.0f, 205.0f + bob2);
    glVertex2f(300.0f, 50.0f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-150.0f, -200.0f);
    glVertex2f(150.0f, -200.0f);
    glVertex2f(180.0f, -220.0f);
    glVertex2f(-180.0f, -220.0f);
    glEnd();

    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-120.0f, -200.0f);
    glVertex2f(120.0f, -200.0f);
    glVertex2f(120.0f, -120.0f);
    glVertex2f(-120.0f, -120.0f);
    glEnd();

    glColor3f(1.0f, 0.7f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(-90.0f, -120.0f);
    glVertex2f(90.0f, -120.0f);
    glVertex2f(90.0f, -60.0f);
    glVertex2f(-90.0f, -60.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-60.0f, -60.0f);
    glVertex2f(60.0f, -60.0f);
    glVertex2f(60.0f, 0.0f);
    glVertex2f(-60.0f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 10.0f, 10.0f, 20);

    for (int i = -1; i <= 1; i += 2) {
        float cx = i * 30.0f;

        glColor3f(0.0f, 0.5f, 1.0f);
        glBegin(GL_POLYGON);
        glVertex2f(cx - 5.0f, 0.0f);
        glVertex2f(cx + 5.0f, 0.0f);
        glVertex2f(cx + 5.0f, 30.0f);
        glVertex2f(cx - 5.0f, 30.0f);
        glEnd();

        float flicker = sinf(time_val * 5.0f + i) * 3.0f;
        glColor3f(1.0f, 0.6f, 0.0f);
        drawCircle(cx, 40.0f + flicker, 7.0f, 20);
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(cx, 38.0f + flicker, 4.0f, 20);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-150.0f, 350.0f, "Happy Birthday!", GLUT_BITMAP_TIMES_ROMAN_24);
    
    glColor3f(1.0f, 0.8f, 0.2f); 
    drawText(-100.0f, 310.0f, "Emon!", GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

void init() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    initConfetti();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Birthday Wish");
    
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}
