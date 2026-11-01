#include <GL/glut.h>
#include <cmath>
#include <string>
#include <vector>

// ---- Global animation state ----
float pulse = 0.0f;        // heart beat scale factor
float timeVal = 0.0f;      // global time for animation
float letterOffset = 0.0f; // for letter floating effect

// ---------------- Heart shape (parametric) ----------------
// Draws a filled heart centered near origin, scaled by 's'
void drawHeart(float s) {
    glBegin(GL_POLYGON);
    // Upper bound for t must cover full heart; use 0..2pi
    for (float t = 0; t <= 2 * 3.14159265f; t += 0.01f) {
        // Classic heart parametric equation
        float x = 16 * pow(sin(t), 3);
        float y = 13 * cos(t) - 5 * cos(2 * t)
                  - 2 * cos(3 * t) - cos(4 * t);
        glVertex2f(x * s, y * s);
    }
    glEnd();
}

// ---------------- Letter drawing using lines ----------------
// Each letter is drawn with simple line segments in a local box.
// Coordinates roughly within [-1,1] x [-1,1], then scaled/translated.

void drawLetterI(float x, float y, float s) {
    glBegin(GL_LINES);
    // vertical bar
    glVertex2f(x, y - s);     glVertex2f(x, y + s);
    // top and bottom serifs
    glVertex2f(x - s*0.5f, y + s); glVertex2f(x + s*0.5f, y + s);
    glVertex2f(x - s*0.5f, y - s); glVertex2f(x + s*0.5f, y - s);
    glEnd();
}

void drawLetterL(float x, float y, float s) {
    glBegin(GL_LINES);
    // vertical
    glVertex2f(x - s*0.4f, y + s); glVertex2f(x - s*0.4f, y - s);
    // bottom horizontal
    glVertex2f(x - s*0.4f, y - s); glVertex2f(x + s*0.4f, y - s);
    glEnd();
}

void drawLetterO(float x, float y, float s) {
    // Approximate circle with line loop
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 40; i++) {
        float a = 2 * 3.14159265f * i / 40;
        glVertex2f(x + cos(a) * s * 0.7f, y + sin(a) * s);
    }
    glEnd();
}

void drawLetterV(float x, float y, float s) {
    glBegin(GL_LINES);
    glVertex2f(x - s*0.7f, y + s);  glVertex2f(x, y - s);
    glVertex2f(x + s*0.7f, y + s);  glVertex2f(x, y - s);
    glEnd();
}

void drawLetterE(float x, float y, float s) {
    glBegin(GL_LINES);
    // vertical
    glVertex2f(x - s*0.5f, y + s); glVertex2f(x - s*0.5f, y - s);
    // top
    glVertex2f(x - s*0.5f, y + s); glVertex2f(x + s*0.5f, y + s);
    // middle
    glVertex2f(x - s*0.5f, y);     glVertex2f(x + s*0.4f, y);
    // bottom
    glVertex2f(x - s*0.5f, y - s); glVertex2f(x + s*0.5f, y - s);
    glEnd();
}

void drawLetterY(float x, float y, float s) {
    glBegin(GL_LINES);
    // upper V
    glVertex2f(x - s*0.6f, y + s); glVertex2f(x, y);
    glVertex2f(x + s*0.6f, y + s); glVertex2f(x, y);
    // stem
    glVertex2f(x, y);              glVertex2f(x, y - s);
    glEnd();
}

void drawLetterU(float x, float y, float s) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - s*0.6f, y + s);
    glVertex2f(x - s*0.6f, y - s*0.4f);
    glVertex2f(x - s*0.3f, y - s);
    glVertex2f(x + s*0.3f, y - s);
    glVertex2f(x + s*0.6f, y - s*0.4f);
    glVertex2f(x + s*0.6f, y + s);
    glEnd();
}

// Smiley :) — colon + parenthesis
void drawSmiley(float x, float y, float s) {
    // Colon (two dots)
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glVertex2f(x, y + s*0.4f);
    glVertex2f(x, y - s*0.4f);
    glEnd();

    // Right parenthesis ) — arc
    glBegin(GL_LINE_STRIP);
    for (int i = -60; i <= 60; i += 5) {
        float a = i * 3.14159265f / 180.0f;
        glVertex2f(x + s*0.6f + cos(a) * s * 0.8f,
                   y + sin(a) * s * 1.0f);
    }
    glEnd();
}

// ---------------- Display ----------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ---- Draw beating heart (red) ----
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    float heartScale = 0.8f + 0.25f * pulse;   // pulsing
    glColor3f(1.0f, 0.1f + 0.2f * pulse, 0.2f);
    drawHeart(heartScale * 1.2f);
    glPopMatrix();

    // ---- Draw "I LOVE YOU" letters ----
    // Slight vertical floating using sin(time)
    float floatY = 0.0f + 0.05f * sin(letterOffset);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    float y = -0.55f + floatY;
    float s = 0.18f;
    float gap = 0.35f;
    float startX = -1.7f;

    drawLetterI(startX + 0*gap, y, s);
    drawLetterL(startX + 1*gap, y, s);
    drawLetterO(startX + 2*gap, y, s);
    drawLetterV(startX + 3*gap, y, s);
    drawLetterE(startX + 4*gap, y, s);
    drawLetterY(startX + 5*gap, y, s);
    drawLetterO(startX + 6*gap, y, s);
    drawLetterU(startX + 7*gap, y, s);

    drawSmiley(startX + 8.5f*gap, y, s);

    glutSwapBuffers();
}

// ---------------- Animation ----------------
void update(int) {
    timeVal += 0.05f;
    // Heart beat: fast rise, slow fall, repeating
    pulse = fabs(sin(timeVal * 2.0f));
    letterOffset = timeVal * 3.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);   // ~60 FPS
}

// ---------------- Init ----------------
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(-2.0, 2.0, -1.5, 1.5);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // double buffer for animation
    glutInitWindowSize(800, 600);
    glutCreateWindow("I LOVE YOU :)");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}