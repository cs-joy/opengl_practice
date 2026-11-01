#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <string>

// ---------- Animation state ----------
float leanAmount = 0.0f;      // 0.0 = standing, 1.0 = fully leaning in
float textAlpha = 0.0f;       // fade-in for "I LOVE..." text
int   phase = 0;              // 0=idle, 1=leaning, 2=text, 3=done
int   frameCounter = 0;

// ---------- Heart pixel data ----------
struct Point { int x, y; };
std::vector<Point> heartPixels;
int heartReveal = 0;

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

// ---------- Filled circle (for head) ----------
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

// ---------- Draw boy (tall, on the left) ----------
// lean: 0 = standing straight, 1 = fully leaning right toward girl
void drawBoy(float lean) {
    float baseX = 280.0f;
    float baseY = 100.0f;

    // Head shifts right and down slightly as he leans
    float headX = baseX + lean * 55.0f;
    float headY = baseY + 340.0f - lean * 15.0f;

    // --- Head ---
    glColor3f(1.0f, 0.85f, 0.7f);  // skin
    drawCircle(headX, headY, 28.0f);

    // --- Hair ---
    glColor3f(0.15f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(headX, headY + 5);
        for (int i = 0; i <= 180; i += 5) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(headX + 30 * cosf(a), headY + 30 * sinf(a));
        }
    glEnd();

    // --- Eye ---
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(headX + 12 + lean * 2, headY + 2, 3.0f);

    // --- Smile (only when kissing) ---
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

    // --- Neck ---
    glColor3f(1.0f, 0.85f, 0.7f);
    drawRect(headX - 8, headY - 40, 16, 15);

    // --- Body (tall torso, leaning forward) ---
    // Use a parallelogram to show leaning
    float shoulderX = baseX + lean * 45.0f;
    float shoulderY = baseY + 300.0f;
    float hipX = baseX;
    float hipY = baseY + 150.0f;

    glColor3f(0.15f, 0.3f, 0.7f);  // blue shirt
    glBegin(GL_QUADS);
        glVertex2f(hipX - 30, hipY);
        glVertex2f(hipX + 30, hipY);
        glVertex2f(shoulderX + 35, shoulderY);
        glVertex2f(shoulderX - 35, shoulderY);
    glEnd();

    // --- Arms (one reaching toward the girl) ---
    glColor3f(1.0f, 0.85f, 0.7f);
    glLineWidth(10.0f);
    glBegin(GL_LINES);
        // Left arm (behind)
        glVertex2f(shoulderX - 30, shoulderY - 10);
        glVertex2f(shoulderX - 60, shoulderY - 80);
        // Right arm (reaching toward girl, extends more with lean)
        glVertex2f(shoulderX + 30, shoulderY - 10);
        glVertex2f(shoulderX + 30 + lean * 60, shoulderY - 60 + lean * 20);
    glEnd();

    // --- Legs (long, tall) ---
    glColor3f(0.1f, 0.1f, 0.2f);  // dark pants
    glLineWidth(14.0f);
    glBegin(GL_LINES);
        glVertex2f(hipX - 18, hipY);
        glVertex2f(hipX - 22, baseY);
        glVertex2f(hipX + 18, hipY);
        glVertex2f(hipX + 22, baseY);
    glEnd();

    // --- Shoes ---
    glColor3f(0.05f, 0.05f, 0.05f);
    drawRect(hipX - 34, baseY - 6, 26, 10);
    drawRect(hipX + 8, baseY - 6, 26, 10);
}

// ---------- Draw girl (shorter, on the right) ----------
void drawGirl() {
    float baseX = 500.0f;
    float baseY = 100.0f;

    float headX = baseX;
    float headY = baseY + 280.0f;

    // --- Hair back ---
    glColor3f(0.35f, 0.15f, 0.05f);  // brown
    drawCircle(headX, headY, 34.0f);
    drawRect(headX - 30, headY - 90, 60, 90);

    // --- Head ---
    glColor3f(1.0f, 0.85f, 0.75f);
    drawCircle(headX, headY, 26.0f);

    // --- Hair on top ---
    glColor3f(0.35f, 0.15f, 0.05f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(headX, headY + 5);
        for (int i = 0; i <= 180; i += 5) {
            float a = i * 3.14159f / 180.0f;
            glVertex2f(headX + 29 * cosf(a), headY + 29 * sinf(a));
        }
    glEnd();

    // --- Eyes (closed, since she's being kissed) ---
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(headX - 15, headY + 3);
        glVertex2f(headX - 7, headY + 3);
        glVertex2f(headX + 7, headY + 3);
        glVertex2f(headX + 15, headY + 3);
    glEnd();

    // --- Blush ---
    glColor3f(1.0f, 0.5f, 0.5f);
    drawCircle(headX - 16, headY - 8, 5.0f);
    drawCircle(headX + 16, headY - 8, 5.0f);

    // --- Smile ---
    glColor3f(0.7f, 0.2f, 0.2f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 10; ++i) {
        float t = i / 10.0f;
        glVertex2f(headX - 7 + t * 14, headY - 12 - sinf(t * 3.14159f) * 3);
    }
    glEnd();

    // --- Neck ---
    glColor3f(1.0f, 0.85f, 0.75f);
    drawRect(headX - 7, headY - 38, 14, 14);

    // --- Dress (triangle shape) ---
    float shoulderY = baseY + 250.0f;
    float hipY = baseY + 120.0f;

    glColor3f(1.0f, 0.3f, 0.5f);  // pink dress
    glBegin(GL_QUADS);
        glVertex2f(headX - 28, shoulderY);
        glVertex2f(headX + 28, shoulderY);
        glVertex2f(headX + 42, hipY);
        glVertex2f(headX - 42, hipY);
    glEnd();

    // Dress skirt (wider at bottom)
    glBegin(GL_QUADS);
        glVertex2f(headX - 42, hipY);
        glVertex2f(headX + 42, hipY);
        glVertex2f(headX + 55, baseY + 60);
        glVertex2f(headX - 55, baseY + 60);
    glEnd();

    // --- Arms ---
    glColor3f(1.0f, 0.85f, 0.75f);
    glLineWidth(9.0f);
    glBegin(GL_LINES);
        // Left arm (reaching toward boy)
        glVertex2f(headX - 25, shoulderY - 10);
        glVertex2f(headX - 65, shoulderY - 50);
        // Right arm (down)
        glVertex2f(headX + 25, shoulderY - 10);
        glVertex2f(headX + 45, shoulderY - 70);
    glEnd();

    // --- Legs ---
    glColor3f(1.0f, 0.85f, 0.75f);
    glLineWidth(11.0f);
    glBegin(GL_LINES);
        glVertex2f(headX - 18, baseY + 60);
        glVertex2f(headX - 20, baseY);
        glVertex2f(headX + 18, baseY + 60);
        glVertex2f(headX + 20, baseY);
    glEnd();

    // --- Shoes ---
    glColor3f(0.8f, 0.1f, 0.3f);
    drawRect(headX - 32, baseY - 6, 24, 10);
    drawRect(headX + 8, baseY - 6, 24, 10);
}

// ---------- Small heart (decorative) ----------
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

// ---------- Kiss sparkle / heart burst ----------
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

// ---------- Draw ground ----------
void drawGround() {
    glColor3f(0.15f, 0.35f, 0.15f);  // dark green
    drawRect(0, 0, 800, 100);
}

// ---------- Display ----------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Background (sky gradient feel — solid dark blue)
    glColor3f(0.08f, 0.08f, 0.18f);
    drawRect(0, 0, 800, 800);

    // Ground
    drawGround();

    // Draw girl first (so boy overlaps when leaning)
    drawGirl();

    // Draw boy with current lean
    drawBoy(leanAmount);

    // Kiss burst when leaning is complete
    if (leanAmount > 0.9f) {
        float burst = (leanAmount - 0.9f) / 0.1f;
        drawKissBurst(430.0f, 400.0f, burst);
    }

    // Text "I LOVE..." after kiss
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
        // Wait a moment before starting
        if (frameCounter > 30) {
            phase = 1;
            frameCounter = 0;
        }
    } else if (phase == 1) {
        // Boy leans in
        leanAmount += 0.015f;
        if (leanAmount >= 1.0f) {
            leanAmount = 1.0f;
            phase = 2;
            frameCounter = 0;
        }
    } else if (phase == 2) {
        // Hold the kiss, then fade in text
        if (frameCounter > 20) {
            textAlpha += 0.03f;
            if (textAlpha >= 1.0f) {
                textAlpha = 1.0f;
                phase = 3;
            }
        }
    }
    // phase 3 = done, hold forever

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // ~60 FPS
}

// ---------- Init ----------
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
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