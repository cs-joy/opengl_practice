#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

// ---------- Structure to hold a pixel point ----------
struct Point {
    int x, y;
};

// ---------- Global data ----------
std::vector<Point> heartPixels;   // All heart pixels, sorted in reveal order
std::vector<Point> textPixels;    // All text pixels, sorted in reveal order
int heartIndex = 0;               // How many heart pixels revealed so far
int textIndex  = 0;               // How many text pixels revealed so far
int totalHeart = 0;
int totalText  = 0;

// ---------- 5x7 bitmap font for "I LOVE YOU :)" ----------
// Each character is 7 rows of 5 bits (from MSB to LSB of a byte, using lower 5 bits)
struct Glyph {
    char c;
    unsigned char rows[7]; // 5 bits used
};

// Bit pattern: bit 4 = leftmost pixel, bit 0 = rightmost pixel
Glyph font5x7[] = {
    {'I', {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111}},
    {' ', {0,0,0,0,0,0,0}},
    {'L', {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b11111}},
    {'O', {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110}},
    {'V', {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01010, 0b00100}},
    {'E', {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b11111}},
    {'Y', {0b10001, 0b10001, 0b01010, 0b00100, 0b00100, 0b00100, 0b00100}},
    {'U', {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110}},
    {'M', {0b10001, 0b11011, 0b10101, 0b10101, 0b10001, 0b10001, 0b10001}},
    {'A', {0b01110, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001}},
    {':', {0b00000, 0b00100, 0b00100, 0b00000, 0b00100, 0b00100, 0b00000}},
    {')', {0b00110, 0b01000, 0b10000, 0b10000, 0b10000, 0b01000, 0b00110}},
};

Glyph* findGlyph(char c) {
    for (auto &g : font5x7) if (g.c == c) return &g;
    return nullptr;
}

// ---------- Convert text string to pixel points ----------
void buildTextPixels(const std::string &text, int startX, int startY, int scale) {
    int cursorX = startX;
    for (char ch : text) {
        if (ch == ' ') { cursorX += 4 * scale; continue; }
        Glyph* g = findGlyph(ch);
        if (!g) { cursorX += 6 * scale; continue; }
        for (int row = 0; row < 7; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (g->rows[row] & (1 << (4 - col))) {
                    // Add each pixel (scale block)
                    for (int sy = 0; sy < scale; ++sy)
                        for (int sx = 0; sx < scale; ++sx)
                            textPixels.push_back({cursorX + col*scale + sx,
                                                  startY - row*scale - sy});
                }
            }
        }
        cursorX += 6 * scale; // 5 wide + 1 space
    }
}

// ---------- Build heart pixels from heart equation ----------
// Heart equation: (x^2 + y^2 - 1)^3 - x^2 * y^3 = 0
// We scale and sample it over a grid, using inside-test.
void buildHeartPixels(int centerX, int centerY, int scale) {
    for (int py = -scale; py <= scale; ++py) {
        for (int px = -scale; px <= scale; ++px) {
            // Normalize coordinates to roughly [-1.5, 1.5]
            double x = (double)px / (scale * 0.75);
            double y = (double)py / (scale * 0.75);

            // Shift so heart is upright (y positive upward)
            double a = x * x + y * y - 1.0;
            double val = a * a * a - x * x * y * y * y;

            if (val <= 0.0) {
                heartPixels.push_back({centerX + px, centerY + py});
            }
        }
    }

    // Sort: top-to-bottom (largest y first), then left-to-right
    std::sort(heartPixels.begin(), heartPixels.end(), [](const Point &a, const Point &b) {
        if (a.y != b.y) return a.y > b.y;  // top to bottom
        return a.x < b.x;                   // left to right
    });
}

// ---------- Initialization ----------
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
    glMatrixMode(GL_MODELVIEW);
    glPointSize(2.0f);
}

// ---------- Build all pixel data ----------
void buildScene() {
    heartPixels.clear();
    textPixels.clear();

    // Heart centered around (400, 480) with scale 200
    buildHeartPixels(400, 480, 200);

    // Text below the heart
    buildTextPixels("I LOVE YOU MA", 220, 180, 5);

    totalHeart = (int)heartPixels.size();
    totalText  = (int)textPixels.size();
}

// ---------- Display ----------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw heart pixels (pink/red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < heartIndex && i < totalHeart; ++i) {
        glVertex2i(heartPixels[i].x, heartPixels[i].y);
    }
    glEnd();

    // Draw text pixels (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < textIndex && i < totalText; ++i) {
        glVertex2i(textPixels[i].x, textPixels[i].y);
    }
    glEnd();

    glFlush();
}

// ---------- Animation ----------
void timer(int value) {
    (void)value;

    if (heartIndex < totalHeart) {
        // Reveal heart in batches
        heartIndex += 40;
        if (heartIndex > totalHeart) heartIndex = totalHeart;
    } else if (textIndex < totalText) {
        // Then reveal text in batches
        textIndex += 15;
        if (textIndex > totalText) textIndex = totalText;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

// ---------- Main ----------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("MA");

    init();
    buildScene();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}