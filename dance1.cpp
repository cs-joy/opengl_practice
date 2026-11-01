#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>

// ---------- Animation state ----------
float leanAmount = 0.0f;
float textAlpha = 0.0f;
int   phase = 0;
int   frameCounter = 0;

// ---------- Heart pixel data (unused in this file but kept) ----------
struct Point { int x, y; };
std::vector<Point> heartPixels;
int heartReveal = 0;

// ---------- Star data ----------
struct Star {
    float x, y;
    float speed;
    float size;
    float brightness;
    float twinkle;
};

std::vector<Star> stars;

// ---------- 5x7 bitmap font ----------
struct Glyph { char c; unsigned char rows[7]; };
Glyph font5x7[] = {
    {'I', {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111}},
    {' ', {0,0,0,0,0,0,0}},
    {'L', {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b11111}},
    {'O', {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110}},
    {'V', {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01010, 0b00100}},
    {'E', {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b11111}},
    {'.', {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00110, 0b00110}},
};
Glyph* findGlyph(char c) {
    for (auto &g : font5x7) if (g.c == c) return &g;
    return nullptr;
}

// Draw a string using the bitmap font at (x, y) with scale
void drawText(const std::string &text, int x, int y, int scale) {
    int cursorX = x;
    for (char ch : text) {
        if (ch == ' ') { cursorX += 4 * scale; continue; }
        Glyph* g = findGlyph(ch);
        if (!g) { cursorX += 6 * scale; continue; }
        for (int row = 0; row < 7; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (g->rows[row] & (1 << (4 - col))) {
                    int px = cursorX + col * scale;
                    int py = y - row * scale;
                    glBegin(GL_QUADS);
                        glVertex2i(px, py);
                        glVertex2i(px + scale, py);
                        glVertex2i(px + scale, py - scale);
                        glVertex2i(px, py - scale);
                    glEnd();
                }
            }
        }
        cursorX += 6 * scale;
    }
}

// ---------- Filled circle ----------
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i += 5) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
        }
    glEnd();
}

// ---------- Filled rectangle ----------
void drawRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

// ---------- Draw boy ----------
void drawBoy(float lean) {
    float baseX = 280.0f;
    float baseY = 100.0f;

    float headX = baseX + lean * 55.0f;
    float headY = baseY + 340.0f - lean * 15.0f;

    glColor3f(1.0f, 0.85f, 0.7f);
    drawCircle(headX, headY, 28.0f);

    glColor3f(0.15f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(headX, headY + 5);
        for (int i = 0; i <= 180; i += 5) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(headX + 30 * cosf(a), headY + 30 * sinf(a));
        }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(headX + 12 + lean * 2, headY + 2, 3.0f);

    if (lean > 0.3f) {
        glColor3f(0.6f, 0.1f, 0.1f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 10; ++i) {
            float t = i / 10.0f;
            glVertex2f(headX + 4 + t * 14, headY - 10 - sinf(t * 3.14159f) * 4);
        }
        glEnd();
    }

    glColor3f(1.0f, 0.85f, 0.7f);
    drawRect(headX - 8, headY - 40, 16, 15);

    float shoulderX = baseX + lean * 45.0f;
    float shoulderY = baseY + 300.0f;
    float hipX = baseX;
    float hipY = baseY + 150.0f;

    glColor3f(0.15f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(hipX - 30, hipY);
        glVertex2f(hipX + 30, hipY);
        glVertex2f(shoulderX + 35, shoulderY);
        glVertex2f(shoulderX - 35, shoulderY);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.7f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
        glVertex2f(shoulderX - 30, shoulderY - 10);
        glVertex2f(shoulderX - 60, shoulderY - 80);
        glVertex2f(shoulderX + 30, shoulderY - 10);
        glVertex2f(shoulderX + 30 + lean * 60, shoulderY - 60 + lean * 20);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.2f);
    glLineWidth(14.0f);
    glBegin(GL_LINES);
        glVertex2f(hipX - 18, hipY);
        glVertex2f(hipX - 22, baseY);
        glVertex2f(hipX + 18, hipY);
        glVertex2f(hipX + 22, baseY);
    glEnd();

    glColor3f(0.05f, 0.05f, 0.05f);
    drawRect(hipX - 34, baseY - 6, 26, 10);
    drawRect(hipX + 8, baseY - 6, 26, 10);
}

// ---------- Draw girl ----------
void drawGirl() {
    float baseX = 500.0f;
    float baseY = 100.0f;

    float headX = baseX;
    float headY = baseY + 280.0f;

    glColor3f(0.35f, 0.15f, 0.05f);
    drawCircle(headX, headY, 34.0f);
    drawRect(headX - 30, headY - 90, 60, 90);

    glColor3f(1.0f, 0.85f, 0.75f);
    drawCircle(headX, headY, 26.0f);

    glColor3f(0.35f, 0.15f, 0.05f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(headX, headY + 5);
        for (int i = 0; i <= 180; i += 5) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(headX + 29 * cosf(a), headY + 29 * sinf(a));
        }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(headX - 15, headY + 3);
        glVertex2f(headX - 7, headY + 3);
        glVertex2f(headX + 7, headY + 3);
        glVertex2f(headX + 15, headY + 3);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.5f);
    drawCircle(headX - 16, headY - 8, 5.0f);
    drawCircle(headX + 16, headY - 8, 5.0f);

    glColor3f(0.7f, 0.2f, 0.2f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 10; ++i) {
        float t = i / 10.0f;
        glVertex2f(headX - 7 + t * 14, headY - 12 - sinf(t * 3.14159f) * 3);
    }
    glEnd();

    glColor3f(1.0f, 0.85f, 0.75f);
    drawRect(headX - 7, headY - 38, 14, 14);

    float shoulderY = baseY + 250.0f;
    float hipY = baseY + 120.0f;

    glColor3f(1.0f, 0.3f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(headX - 28, shoulderY);
        glVertex2f(headX + 28, shoulderY);
        glVertex2f(headX + 42, hipY);
        glVertex2f(headX - 42, hipY);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(headX - 42, hipY);
        glVertex2f(headX + 42, hipY);
        glVertex2f(headX + 55, baseY + 60);
        glVertex2f(headX - 55, baseY + 60);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.75f);
    glLineWidth(9.0f);
    glBegin(GL_LINES);
        glVertex2f(headX - 25, shoulderY - 10);
        glVertex2f(headX - 65, shoulderY - 50);
        glVertex2f(headX + 25, shoulderY - 10);
        glVertex2f(headX + 45, shoulderY - 70);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.75f);
    glLineWidth(11.0f);
    glBegin(GL_LINES);
        glVertex2f(headX - 18, baseY + 60);
        glVertex2f(headX - 20, baseY);
        glVertex2f(headX + 18, baseY + 60);
        glVertex2f(headX + 20, baseY);
    glEnd();

    glColor3f(0.8f, 0.1f, 0.3f);
    drawRect(headX - 32, baseY - 6, 24, 10);
    drawRect(headX + 8, baseY - 6, 24, 10);
}

// ---------- Small heart ----------
void drawSmallHeart(float cx, float cy, float size) {
    glColor3f(1.0f, 0.2f, 0.4f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 360; i += 10) {
            float t = i * 3.14159f / 180.0f;
            float x = 16 * powf(sinf(t), 3);
            float y = 13 * cosf(t) - 5 * cosf(2*t) - 2 * cosf(3*t) - cosf(4*t);
            glVertex2f(cx + x * size / 16.0f, cy + y * size / 16.0f);
        }
    glEnd();
}

// ---------- Kiss burst ----------
void drawKissBurst(float x, float y, float progress) {
    if (progress <= 0.0f) return;
    for (int i = 0; i < 6; ++i) {
        float angle = i * 60.0f * 3.14159f / 180.0f;
        float dist = progress * 40.0f;
        float px = x + cosf(angle) * dist;
        float py = y + sinf(angle) * dist;
        float sz = 6.0f * (1.0f - progress * 0.5f);
        glColor3f(1.0f, 0.4f - progress * 0.3f, 0.6f);
        drawSmallHeart(px, py, sz);
    }
}

// ---------- Ground ----------
void drawGround() {
    glColor3f(0.15f, 0.35f, 0.15f);
    drawRect(0, 0, 800, 100);
}

// ---------- Stars ----------
void spawnStars(int count) {
    stars.clear();
    for (int i = 0; i < count; ++i) {
        Star s;
        s.x = (float)(rand() % 800);
        // Start spread across whole height, then they fall
        s.y = (float)(rand() % 900) + 400;
        s.speed = 1.0f + (rand() % 100) / 40.0f;   // 1.0 - 3.5 px/frame
        s.size = 1.0f + (rand() % 30) / 15.0f;      // 1.0 - 3.0 px radius
        s.brightness = 0.6f + (rand() % 40) / 100.0f; // 0.6 - 1.0
        s.twinkle = (float)(rand() % 628) / 100.0f;  // 0 - 2π
        stars.push_back(s);
    }
}

void updateStars() {
    for (auto &s : stars) {
        s.y -= s.speed;
        s.twinkle += 0.15f;
        // Recycle to top when it falls below the ground
        if (s.y < 0.0f) {
            s.y = 850.0f + (rand() % 100);
            s.x = (float)(rand() % 800);
            s.speed = 1.0f + (rand() % 100) / 40.0f;
            s.size = 1.0f + (rand() % 30) / 15.0f;
            s.brightness = 0.6f + (rand() % 40) / 100.0f;
        }
    }
}

void drawStars() {
    for (auto &s : stars) {
        // Twinkle effect: brightness oscillates
        float tw = 0.75f + 0.25f * sinf(s.twinkle);
        float b = s.brightness * tw;

        // Outer glow
        glColor4f(1.0f, 1.0f, 0.9f, b * 0.3f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        drawCircle(s.x, s.y, s.size * 2.0f);

        // Core
        glColor4f(1.0f, 1.0f, 1.0f, b);
        drawCircle(s.x, s.y, s.size);

        glDisable(GL_BLEND);
    }
}

// ---------- Display ----------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glColor3f(0.08f, 0.08f, 0.18f);
    drawRect(0, 0, 800, 800);

    // Ground
    drawGround();

    // Stars (behind characters) — only after kiss phase
    if (phase >= 3) {
        drawStars();
    }

    // Characters
    drawGirl();
    drawBoy(leanAmount);

    // Kiss burst
    if (leanAmount > 0.9f) {
        float burst = (leanAmount - 0.9f) / 0.1f;
        drawKissBurst(430.0f, 400.0f, burst);
    }

    // Text
    if (textAlpha > 0.0f) {
        glColor4f(1.0f, 0.3f, 0.5f, textAlpha);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        drawText("I LOVE...", 250, 720, 8);
        glDisable(GL_BLEND);
    }

    glFlush();
}

// ---------- Animation timer ----------
void timer(int value) {
    (void)value;
    frameCounter++;

    if (phase == 0) {
        if (frameCounter > 30) {
            phase = 1;
            frameCounter = 0;
        }
    } else if (phase == 1) {
        leanAmount += 0.015f;
        if (leanAmount >= 1.0f) {
            leanAmount = 1.0f;
            phase = 2;
            frameCounter = 0;
        }
    } else if (phase == 2) {
        if (frameCounter > 20) {
            textAlpha += 0.03f;
            if (textAlpha >= 1.0f) {
                textAlpha = 1.0f;
                phase = 3;
                spawnStars(120);   // <-- start the star rain
            }
        }
    } else if (phase == 3) {
        updateStars();             // <-- animate the falling stars
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ---------- Init ----------
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    srand(12345);  // fixed seed = same star layout every run
}

// ---------- Main ----------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("A Boy Kisses a Girl - I LOVE...");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}