#include <GL/glut.h>
#include <cmath>

// ---------- Bresenham Line Algorithm (general, works for all slopes) ----------
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
    glEnd();
}

// ---------- Helper: draw a filled-ish heart using two circles and a triangle ----------
void drawHeart(int cx, int cy, int size) {
    // Heart made of points using a parametric heart equation
    glBegin(GL_POINTS);
    for (float t = 0; t < 6.28318f; t += 0.005f) {
        float x = 16 * pow(sin(t), 3);
        float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
        glVertex2i(cx + (int)(x * size / 16.0f), cy + (int)(y * size / 16.0f));
    }
    glEnd();
}

// ---------- Letters ----------
void drawI(int x, int y) {
    // Vertical bar
    drawLine(x, y, x, y + 100);
    // Top and bottom serifs
    drawLine(x - 15, y + 100, x + 15, y + 100);
    drawLine(x - 15, y, x + 15, y);
}

void drawY(int x, int y) {
    // Two upper arms
    drawLine(x, y + 100, x + 20, y + 50);
    drawLine(x + 40, y + 100, x + 20, y + 50);
    // Stem
    drawLine(x + 20, y + 50, x + 20, y);
}

void drawO(int x, int y) {
    // Draw an O using ellipse points
    int cx = x + 25;
    int cy = y + 50;
    int rx = 25;
    int ry = 50;
    glBegin(GL_POINTS);
    for (float t = 0; t < 6.28318f; t += 0.003f) {
        glVertex2i(cx + (int)(rx * cos(t)), cy + (int)(ry * sin(t)));
    }
    glEnd();
}

void drawU(int x, int y) {
    // Left side
    drawLine(x, y + 100, x, y + 25);
    // Right side
    drawLine(x + 40, y + 100, x + 40, y + 25);
    // Bottom curve (approximate with points)
    int cx = x + 20;
    int cy = y + 25;
    glBegin(GL_POINTS);
    for (float t = 3.14159f; t < 6.28318f; t += 0.01f) {
        glVertex2i(cx + (int)(20 * cos(t)), cy + (int)(25 * sin(t)));
    }
    glEnd();
}

void drawColon(int x, int y) {
    // Two dots
    for (int i = -3; i <= 3; i++)
        for (int j = -3; j <= 3; j++) {
            if (i*i + j*j <= 9) {
                glBegin(GL_POINTS);
                glVertex2i(x + i, y + 75 + j);
                glVertex2i(x + i, y + 25 + j);
                glEnd();
            }
        }
}

void drawSmiley(int x, int y) {
    int cx = x + 25;
    int cy = y + 50;
    int r  = 50;

    // Circle outline
    glBegin(GL_POINTS);
    for (float t = 0; t < 6.28318f; t += 0.003f) {
        glVertex2i(cx + (int)(r * cos(t)), cy + (int)(r * sin(t)));
    }
    glEnd();

    // Eyes (filled dots)
    for (int i = -3; i <= 3; i++)
        for (int j = -3; j <= 3; j++) {
            if (i*i + j*j <= 9) {
                glBegin(GL_POINTS);
                glVertex2i(cx - 15 + i, cy + 15 + j);
                glVertex2i(cx + 15 + i, cy + 15 + j);
                glEnd();
            }
        }

    // Smile (arc)
    glBegin(GL_POINTS);
    for (float t = 3.14159f + 0.3f; t < 6.28318f - 0.3f; t += 0.01f) {
        glVertex2i(cx + (int)(28 * cos(t)), cy - 10 + (int)(20 * sin(t)));
    }
    glEnd();
}

// ---------- Display ----------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Row 1: "I" and a red heart
    glColor3f(1.0f, 1.0f, 1.0f);
    drawI(40, 350);

    glColor3f(1.0f, 0.1f, 0.3f);   // Red heart
    drawHeart(130, 400, 55);

    // Row 2: "YOU"
    glColor3f(0.3f, 0.8f, 1.0f);   // Cyan
    drawY(230, 350);
    drawO(290, 350);
    drawU(360, 350);

    // Row 3: ":)"
    glColor3f(1.0f, 1.0f, 0.0f);   // Yellow
    drawColon(440, 350);
    drawSmiley(130, 150);

    // Small heart next to smiley
    glColor3f(1.0f, 0.4f, 0.7f);
    drawHeart(280, 200, 35);

    glFlush();
}

// ---------- Init ----------
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// ---------- Main ----------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("I LOVE YOU :)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}