#include <GL/glut.h>
#include <string>
#include <cmath>

// ---------- Simple vector font (7-segment style for letters we need) ----------
// Each letter is drawn using line segments within a 0..10 x 0..14 box.

void drawChar(char c, float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1);

    glLineWidth(2.0);

    switch (c) {
        case 'I':
            glBegin(GL_LINES);
            glVertex2f(0, 0);  glVertex2f(6, 0);
            glVertex2f(3, 0);  glVertex2f(3, 14);
            glVertex2f(0, 14); glVertex2f(6, 14);
            glEnd();
            break;
        case 'L':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(0, 0);
            glVertex2f(0, 0);  glVertex2f(6, 0);
            glEnd();
            break;
        case 'O':
            glBegin(GL_LINE_LOOP);
            glVertex2f(0, 0);
            glVertex2f(6, 0);
            glVertex2f(6, 14);
            glVertex2f(0, 14);
            glEnd();
            break;
        case 'V':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(3, 0);
            glVertex2f(3, 0);  glVertex2f(6, 14);
            glEnd();
            break;
        case 'E':
            glBegin(GL_LINES);
            glVertex2f(6, 14); glVertex2f(0, 14);
            glVertex2f(0, 14); glVertex2f(0, 0);
            glVertex2f(0, 0);  glVertex2f(6, 0);
            glVertex2f(0, 7);  glVertex2f(5, 7);
            glEnd();
            break;
        case 'Y':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(3, 7);
            glVertex2f(6, 14); glVertex2f(3, 7);
            glVertex2f(3, 7);  glVertex2f(3, 0);
            glEnd();
            break;
        case 'U':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(0, 0);
            glVertex2f(0, 0);  glVertex2f(6, 0);
            glVertex2f(6, 0);  glVertex2f(6, 14);
            glEnd();
            break;
        case 'K':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(0, 0);
            glVertex2f(0, 7);  glVertex2f(6, 14);
            glVertex2f(0, 7);  glVertex2f(6, 0);
            glEnd();
            break;
        case 'H':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(0, 0);
            glVertex2f(6, 14); glVertex2f(6, 0);
            glVertex2f(0, 7);  glVertex2f(6, 7);
            glEnd();
            break;
        case 'A':
            glBegin(GL_LINES);
            glVertex2f(0, 0);  glVertex2f(3, 14);
            glVertex2f(3, 14); glVertex2f(6, 0);
            glVertex2f(1, 5);  glVertex2f(5, 5);
            glEnd();
            break;
        case 'D':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(0, 0);
            glVertex2f(0, 14); glVertex2f(4, 14);
            glVertex2f(4, 14); glVertex2f(6, 11);
            glVertex2f(6, 11); glVertex2f(6, 3);
            glVertex2f(6, 3);  glVertex2f(4, 0);
            glVertex2f(4, 0);  glVertex2f(0, 0);
            glEnd();
            break;
        case 'Z':
            glBegin(GL_LINES);
            glVertex2f(0, 14); glVertex2f(6, 14);
            glVertex2f(6, 14); glVertex2f(0, 0);
            glVertex2f(0, 0);  glVertex2f(6, 0);
            glEnd();
            break;
        case ':':
            glBegin(GL_QUADS);
            glVertex2f(2, 4); glVertex2f(4, 4); glVertex2f(4, 6); glVertex2f(2, 6);
            glVertex2f(2, 9); glVertex2f(4, 9); glVertex2f(4, 11); glVertex2f(2, 11);
            glEnd();
            break;
        case ')':
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= 20; i++) {
                float a = -1.57f + (3.14f * i / 20.0f);
                glVertex2f(3 + 3 * cos(a), 7 + 7 * sin(a));
            }
            glEnd();
            break;
        case ' ':
            break;
        default:
            break;
    }

    glPopMatrix();
}

void drawString(const std::string& s, float x, float y, float scale) {
    float cx = x;
    for (char c : s) {
        drawChar(c, cx, y, scale);
        cx += 8 * scale; // advance width
    }
}

// ---------- Heart shape using parametric equation ----------
void drawHeart(float cx, float cy, float size) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float t = i * 3.14159f / 180.0f;
        // Heart parametric equations
        float x = 16 * pow(sin(t), 3);
        float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
        glVertex2f(cx + x * size, cy + y * size);
    }
    glEnd();
}

// ---------- Bresenham line (bonus, drawn as decoration) ----------
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
    glEnd();
}

// ---------- Display ----------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a big red heart
    glColor3f(1.0f, 0.1f, 0.2f);
    drawHeart(250, 320, 8.0f);

    // Draw "I LOVE YOU KHADIZA :)" in white
    glColor3f(1.0f, 1.0f, 1.0f);
    drawString("I LOVE YOU", 110, 120, 2.5f);
    drawString("KHADIZA :)", 130, 60, 2.5f);

    // Decorative Bresenham lines framing the message
    glColor3f(1.0f, 0.8f, 0.0f); // golden
    bresenhamLine(50, 40, 450, 40);
    bresenhamLine(50, 40, 50, 200);
    bresenhamLine(450, 40, 450, 200);

    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("I LOVE YOU KHADIZA :)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}