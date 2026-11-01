#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <cstdlib>

// ---------- Constants ----------
const int W = 800;
const int H = 800;

// ---------- Helpers ----------
void drawRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i += 6) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
        }
    glEnd();
}

// A simple leaf: pointed oval with a midrib line
// angle in degrees, length and width in pixels
void drawLeaf(float x, float y, float length, float width, float angle,
              float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    // Leaf body (two arcs)
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        // right side up
        for (int i = 0; i <= 20; ++i) {
            float t = i / 20.0f;
            float px = t * length;
            float py = sinf(t * 3.14159f) * width * 0.5f;
            glVertex2f(px, py);
        }
        // left side down
        for (int i = 20; i >= 0; --i) {
            float t = i / 20.0f;
            float px = t * length;
            float py = -sinf(t * 3.14159f) * width * 0.5f;
            glVertex2f(px, py);
        }
    glEnd();

    // Midrib (darker line)
    glColor3f(r * 0.6f, g * 0.6f, b * 0.6f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(length, 0);
    glEnd();

    glPopMatrix();
}

// A leaf with yellow spots (Dieffenbachia style)
void drawSpottedLeaf(float x, float y, float length, float width, float angle) {
    // Base dark green leaf
    drawLeaf(x, y, length, width, angle, 0.06f, 0.22f, 0.10f);

    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    // Yellow spots
    glColor3f(0.95f, 0.92f, 0.30f);
    struct Spot { float t, off, r; };
    Spot spots[] = {
        {0.15f,  0.10f, 3.0f}, {0.25f, -0.15f, 2.5f},
        {0.35f,  0.20f, 3.5f}, {0.45f, -0.05f, 2.0f},
        {0.55f,  0.15f, 3.0f}, {0.65f, -0.20f, 2.5f},
        {0.75f,  0.05f, 3.5f}, {0.85f, -0.10f, 2.0f},
        {0.30f,  0.00f, 2.0f}, {0.50f,  0.25f, 2.5f},
    };
    for (auto &s : spots) {
        float px = s.t * length;
        float py = s.off * width * 0.5f;
        drawCircle(px, py, s.r);
    }

    glPopMatrix();
}

// Simple vine with circular green leaves (pothos)
void drawPothosVine(float baseX, float baseY, float angle, float length, int leafCount) {
    float rad = angle * 3.14159f / 180.0f;
    float ex = baseX + cosf(rad) * length;
    float ey = baseY + sinf(rad) * length;

    // Stem
    glColor3f(0.20f, 0.45f, 0.20f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(baseX, baseY);
        glVertex2f(ex, ey);
    glEnd();

    // Leaves along the stem
    for (int i = 0; i < leafCount; ++i) {
        float t = (i + 1.0f) / (leafCount + 1);
        float px = baseX + cosf(rad) * length * t;
        float py = baseY + sinf(rad) * length * t;
        float side = (i % 2 == 0) ? 1.0f : -1.0f;
        float leafAngle = angle + side * 55.0f;
        drawLeaf(px, py, 45.0f, 40.0f, leafAngle, 0.22f, 0.55f, 0.22f);
    }
}

// ---------- Scene parts ----------

// Tiled floor with faint grout lines
void drawFloor() {
    // Base light gray
    glColor3f(0.86f, 0.86f, 0.84f);
    drawRect(0, 0, W, 520);

    // Grout lines (faint)
    glColor3f(0.78f, 0.78f, 0.76f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        // horizontal lines
        for (int y = 60; y < 520; y += 130) {
            glVertex2f(0, y);
            glVertex2f(W, y);
        }
        // vertical lines
        for (int x = 0; x < W; x += 150) {
            glVertex2f(x, 0);
            glVertex2f(x, 520);
        }
    glEnd();
}

// Gray wall with baseboard
void drawWall() {
    // Wall (light gray, slightly darker than floor)
    glColor3f(0.72f, 0.74f, 0.74f);
    drawRect(0, 520, W, H - 520);

    // Baseboard (white strip)
    glColor3f(0.92f, 0.92f, 0.90f);
    drawRect(0, 500, W, 30);

    // Baseboard shadow line
    glColor3f(0.55f, 0.55f, 0.55f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2f(0, 500);
        glVertex2f(W, 500);
    glEnd();
}

// Glass vase with visible roots
void drawVase(float cx, float cy) {
    // Vase body: trapezoid (wider top, narrower bottom)
    glColor4f(0.75f, 0.78f, 0.80f, 0.55f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
        glVertex2f(cx - 65, cy + 130);
        glVertex2f(cx + 65, cy + 130);
        glVertex2f(cx + 40, cy);
        glVertex2f(cx - 40, cy);
    glEnd();

    // Glass outline
    glColor4f(0.55f, 0.58f, 0.60f, 0.9f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(cx - 65, cy + 130);
        glVertex2f(cx + 65, cy + 130);
        glVertex2f(cx + 40, cy);
        glVertex2f(cx - 40, cy);
    glEnd();

    // Water line (subtle)
    glColor4f(0.70f, 0.85f, 0.90f, 0.5f);
    drawRect(cx - 60, cy + 90, 120, 4);

    // Roots (brown tangles)
    glColor3f(0.45f, 0.30f, 0.15f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        for (int i = 0; i < 14; ++i) {
            float sx = cx - 35 + (i * 5) % 70;
            float sy = cy + 95;
            float ex = cx - 25 + (i * 13) % 60;
            float ey = cy + 15 + (i * 9) % 40;
            glVertex2f(sx, sy);
            glVertex2f(ex, ey);
        }
        // extra tangle
        for (int i = 0; i < 8; ++i) {
            float sx = cx - 25 + (i * 7) % 50;
            float sy = cy + 60;
            float ex = cx - 20 + (i * 11) % 55;
            float ey = cy + 25 + (i * 5) % 30;
            glVertex2f(sx, sy);
            glVertex2f(ex, ey);
        }
    glEnd();

    glDisable(GL_BLEND);
}

// Tall plant (peace lily / dracaena-like) on the right
void drawTallPlant(float baseX, float baseY) {
    // Pot (terracotta)
    glColor3f(0.65f, 0.35f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(baseX - 55, baseY + 80);
        glVertex2f(baseX + 55, baseY + 80);
        glVertex2f(baseX + 40, baseY);
        glVertex2f(baseX - 40, baseY);
    glEnd();
    // Pot rim
    glColor3f(0.75f, 0.42f, 0.25f);
    drawRect(baseX - 58, baseY + 75, 116, 12);

    // Stems (long, curving upward)
    glColor3f(0.20f, 0.40f, 0.18f);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(baseX - 5, baseY + 85);
        glVertex2f(baseX - 15, baseY + 250);
        glVertex2f(baseX - 20, baseY + 380);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(baseX + 5, baseY + 85);
        glVertex2f(baseX + 15, baseY + 300);
        glVertex2f(baseX + 25, baseY + 430);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(baseX + 15, baseY + 85);
        glVertex2f(baseX + 35, baseY + 250);
        glVertex2f(baseX + 55, baseY + 370);
    glEnd();

    // Long leaves at various angles
    drawLeaf(baseX - 20, baseY + 380, 130, 40, 100, 0.20f, 0.50f, 0.20f);
    drawLeaf(baseX - 20, baseY + 380, 120, 38, 80,  0.22f, 0.55f, 0.22f);
    drawLeaf(baseX - 20, baseY + 380, 140, 42, 120, 0.18f, 0.48f, 0.18f);
    drawLeaf(baseX + 25, baseY + 430, 140, 45, 70,  0.20f, 0.55f, 0.20f);
    drawLeaf(baseX + 25, baseY + 430, 130, 40, 50,  0.24f, 0.58f, 0.24f);
    drawLeaf(baseX + 55, baseY + 370, 130, 40, 30,  0.20f, 0.50f, 0.20f);
    drawLeaf(baseX + 55, baseY + 370, 120, 38, 10,  0.22f, 0.55f, 0.22f);
    drawLeaf(baseX + 10, baseY + 300, 120, 38, 85,  0.22f, 0.52f, 0.22f);
}

// ---------- Display ----------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Wall + floor
    drawWall();
    drawFloor();

    // --- Shadows on the floor (soft ellipses under each plant) ---
    glColor4f(0.35f, 0.38f, 0.36f, 0.35f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Vase shadow
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(280, 40);
        for (int i = 0; i <= 360; i += 6) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(280 + 120 * cosf(a), 40 + 30 * sinf(a));
        }
    glEnd();

    // Tall plant shadow (extends to right)
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(620, 30);
        for (int i = 0; i <= 360; i += 6) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(620 + 160 * cosf(a), 30 + 35 * sinf(a));
        }
    glEnd();

    // Spotted leaf shadow (long, angled to right)
    glPushMatrix();
    glTranslatef(600, 50, 0);
    glRotatef(-15, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for (int i = 0; i <= 360; i += 6) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(200 * cosf(a), 20 * sinf(a));
        }
    glEnd();
    glPopMatrix();

    glDisable(GL_BLEND);

    // --- Plants ---

    // 1) Tall plant (peace lily) — drawn first (back layer)
    drawTallPlant(620, 220);

    // 2) Vase with pothos (left-center)
    drawVase(290, 220);

    // Pothos vines from vase
    drawPothosVine(280, 330, 140, 220, 6);   // left vine
    drawPothosVine(290, 330, 70,  250, 7);   // up-left vine
    drawPothosVine(300, 330, 20,  220, 6);   // up vine
    drawPothosVine(310, 330, -30, 200, 5);   // up-right vine
    drawPothosVine(310, 330, -70, 180, 4);   // right vine

    // 3) Spotted leaf (Dieffenbachia) — big dark leaf with yellow spots
    drawSpottedLeaf(430, 330, 200, 110, -25);
    drawSpottedLeaf(360, 300, 170, 95,  -45);
    drawSpottedLeaf(480, 280, 160, 90,  -10);

    // 4) Thin dark vine/stem across the front
    glColor3f(0.15f, 0.10f, 0.08f);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(200, 340);
        glVertex2f(300, 300);
        glVertex2f(420, 320);
        glVertex2f(520, 290);
    glEnd();

    glFlush();
}

// ---------- Init ----------
void init() {
    glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, W, 0, H);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
}

// ---------- Main ----------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Plants on the Floor");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}