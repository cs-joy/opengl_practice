// #include <GL/glut.h>
// #include <string>

// // Configuration constants
// const int WINDOW_WIDTH = 1000;
// const int WINDOW_HEIGHT = 700;
// const float ORTHO_X = 300.0f;
// const float ORTHO_Y = 210.0f;

// // Base rectangle dimensions and position
// const float RECT_X = 30.0f;
// const float RECT_Y = 20.0f;
// const float RECT_W = 80.0f;
// const float RECT_H = 40.0f;

// // Helper to draw a standard 2D rectangle (unfilled)
// void drawRectangle(float x, float y, float w, float h) {
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(x, y);
//     glVertex2f(x + w, y);
//     glVertex2f(x + w, y + h);
//     glVertex2f(x, y + h);
//     glEnd();
// }

// // Helper to render bitmap text for labels
// void drawText(const char* text, float x, float y) {
//     glRasterPos2f(x, y);
//     while (*text) {
//         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text);
//         text++;
//     }
// }

// // Apply an X-shear transformation matrix
// void applyXShear(float shx) {
//     // OpenGL matrices are column-major
//     GLfloat m[16] = {
//         1.0f, 0.0f, 0.0f, 0.0f, // Column 0
//         shx,  1.0f, 0.0f, 0.0f, // Column 1: y contributes to x'
//         0.0f, 0.0f, 1.0f, 0.0f, // Column 2
//         0.0f, 0.0f, 0.0f, 1.0f  // Column 3
//     };
//     glMultMatrixf(m);
// }

// // Apply a Y-shear transformation matrix
// void applyYShear(float shy) {
//     GLfloat m[16] = {
//         1.0f, shy,  0.0f, 0.0f, // Column 0: x contributes to y'
//         0.0f, 1.0f, 0.0f, 0.0f, // Column 1
//         0.0f, 0.0f, 1.0f, 0.0f, // Column 2
//         0.0f, 0.0f, 0.0f, 1.0f  // Column 3
//     };
//     glMultMatrixf(m);
// }

// void display() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     // 1. Draw Coordinate Axes
//     glColor3f(0.4f, 0.4f, 0.4f);
//     glLineWidth(1.0f);
//     glBegin(GL_LINES);
//     // X-axis
//     glVertex2f(-ORTHO_X, 0.0f);
//     glVertex2f(ORTHO_X, 0.0f);
//     // Y-axis
//     glVertex2f(0.0f, -ORTHO_Y);
//     glVertex2f(0.0f, ORTHO_Y);
//     glEnd();
    
//     drawText("X", ORTHO_X - 10.0f, -10.0f);
//     drawText("Y", 10.0f, ORTHO_Y - 15.0f);

//     // Set styling for shapes (Dark blue lines matching the photo reference)
//     glColor3f(0.1f, 0.3f, 0.5f);
//     glLineWidth(1.5f);

//     // 2. Original Rectangle (Quadrant 1)
//     drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
//     drawText("Original", RECT_X + 10.0f, RECT_Y - 15.0f);

//     // 3. Reflected about Y (Quadrant 2)
//     glPushMatrix();
//     glScalef(-1.0f, 1.0f, 1.0f); // Invert X coordinates
//     drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
//     glPopMatrix();
//     drawText("Reflected about Y", -RECT_X - RECT_W + 5.0f, RECT_Y - 15.0f);

//     // 4. Reflected about X (Quadrant 4)
//     glPushMatrix();
//     glScalef(1.0f, -1.0f, 1.0f); // Invert Y coordinates
//     drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
//     glPopMatrix();
//     drawText("Reflected about X", RECT_X + 5.0f, -RECT_Y - RECT_H - 15.0f);

//     // 5. X-Shear (Quadrant 1)
//     glPushMatrix();
//     applyXShear(1.2f); 
//     drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
//     glPopMatrix();
//     drawText("X-Shear", RECT_X + RECT_W + 20.0f, RECT_Y + RECT_H + 5.0f);

//     // 6. Y-Shear (Quadrant 1)
//     glPushMatrix();
//     applyYShear(1.2f);
//     drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
//     glPopMatrix();
//     drawText("Y-Shear", RECT_X + 15.0f, RECT_Y + RECT_H + 55.0f);

//     glFlush();
// }

// void init() {
//     // Light cyan/white background to mimic the monitor screen in the source image
//     glClearColor(0.88f, 0.93f, 0.95f, 1.0f);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     // Establish a 2D Cartesian coordinate system with (0,0) at the center
//     gluOrtho2D(-ORTHO_X, ORTHO_X, -ORTHO_Y, ORTHO_Y);
//     glMatrixMode(GL_MODELVIEW);
// }

// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//     glutInitWindowPosition(100, 100);
//     glutCreateWindow("LAB");
    
//     init();
//     glutDisplayFunc(display);
    
//     glutMainLoop();
//     return 0;
// }

#include <GL/glut.h> // Includes the OpenGL Utility Toolkit for window management and rendering
#include <string>

// --- Configuration Constants ---
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
// ORTHO limits define our 2D coordinate system. 
// We use a range of -300 to 300 on the X axis, making 0 the exact horizontal center.
const float ORTHO_X = 300.0f;
const float ORTHO_Y = 210.0f;

// Base rectangle dimensions and starting position (Quadrant 1)
const float RECT_X = 30.0f;
const float RECT_Y = 20.0f;
const float RECT_W = 80.0f;
const float RECT_H = 40.0f;

// --- Helper Functions ---

/*
 * Draws a basic 2D rectangle.
 * GL_LINE_LOOP connects each vertex to the next, and connects the last back to the first.
 * This function does NOT handle transformations; it always draws based on the exact coordinates passed.
 * We rely on OpenGL's matrix manipulation to move, scale, or shear it before calling this.
 */
void drawRectangle(float x, float y, float w, float h) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);           // Bottom-left
    glVertex2f(x + w, y);       // Bottom-right
    glVertex2f(x + w, y + h);   // Top-right
    glVertex2f(x, y + h);       // Top-left
    glEnd();
}

/*
 * Renders basic bitmap text for labeling our shapes.
 * glRasterPos2f sets the starting coordinate for the text.
 */
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text);
        text++;
    }
}

/*
 * X-Shear pushes the top of a shape horizontally based on its Y height.
 * The mathematical formula is: X_new = X_old + (ShearX * Y_old).
 * OpenGL does not have a glShear() function, so we build the 4x4 Transformation Matrix manually.
 * Note: OpenGL matrices are COLUMN-MAJOR (read top-to-bottom, then left-to-right).
 */
void applyXShear(float shx) {
    GLfloat m[16] = {
        1.0f, 0.0f, 0.0f, 0.0f, // Column 0: X axis basis vector
        shx,  1.0f, 0.0f, 0.0f, // Column 1: Y axis basis vector (Notice 'shx' is here. This adds Y to X)
        0.0f, 0.0f, 1.0f, 0.0f, // Column 2: Z axis basis vector
        0.0f, 0.0f, 0.0f, 1.0f  // Column 3: Translation vector
    };
    // Multiplies the current matrix (the ModelView) by our custom shear matrix
    glMultMatrixf(m);
}

/*
 * Y-Shear pushes the right side of a shape vertically based on its X width.
 * The mathematical formula is: Y_new = Y_old + (ShearY * X_old).
 */
void applyYShear(float shy) {
    GLfloat m[16] = {
        1.0f, shy,  0.0f, 0.0f, // Column 0: Notice 'shy' is here. This adds X to Y.
        0.0f, 1.0f, 0.0f, 0.0f, // Column 1
        0.0f, 0.0f, 1.0f, 0.0f, // Column 2
        0.0f, 0.0f, 0.0f, 1.0f  // Column 3
    };
    glMultMatrixf(m);
}

// --- Main Render Loop ---

void display() {
    // Clears the color buffer (paints the screen the background color set in init)
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. Draw Coordinate Axes (The cross in the center)
    glColor3f(0.4f, 0.4f, 0.4f); // Set color to gray
    glLineWidth(1.0f);
    glBegin(GL_LINES); // Draws independent line segments
    // X-axis (from far left to far right)
    glVertex2f(-ORTHO_X, 0.0f);
    glVertex2f(ORTHO_X, 0.0f);
    // Y-axis (from far bottom to far top)
    glVertex2f(0.0f, -ORTHO_Y);
    glVertex2f(0.0f, ORTHO_Y);
    glEnd();
    
    drawText("X", ORTHO_X - 10.0f, -10.0f);
    drawText("Y", 10.0f, ORTHO_Y - 15.0f);

    // Set styling for our actual shapes (Dark blue lines)
    glColor3f(0.1f, 0.3f, 0.5f);
    glLineWidth(1.5f);

    // 2. Original Rectangle (Quadrant 1)
    // Drawn exactly where we defined it, no matrix modifications yet.
    drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
    drawText("Original", RECT_X + 10.0f, RECT_Y - 15.0f);

    // 3. Reflected about Y (Quadrant 2)
    /* 
     * glPushMatrix() saves the current transformation state.
     * We do this so the reflection we apply here doesn't permanently ruin the canvas for the next shapes.
     */
    glPushMatrix();
    // A reflection across the Y axis is mathematically identical to multiplying all X coordinates by -1.
    // glScalef(x, y, z) scales the axes. Scaling X by -1 flips it over the Y-axis.
    glScalef(-1.0f, 1.0f, 1.0f); 
    drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
    // glPopMatrix() undoes the glScalef and restores the matrix to how it was before we pushed it.
    glPopMatrix(); 
    drawText("Reflected about Y", -RECT_X - RECT_W + 5.0f, RECT_Y - 15.0f);

    // 4. Reflected about X (Quadrant 4)
    glPushMatrix();
    // Multiplying all Y coordinates by -1 flips the shape upside down across the X-axis.
    glScalef(1.0f, -1.0f, 1.0f); 
    drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
    glPopMatrix();
    drawText("Reflected about X", RECT_X + 5.0f, -RECT_Y - RECT_H - 15.0f);

    // 5. X-Shear (Quadrant 1)
    glPushMatrix();
    // Applies our custom 4x4 matrix. 
    // This skews the shape to the right. The top moves further right than the bottom because its Y is higher.
    applyXShear(1.2f); 
    drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
    glPopMatrix();
    drawText("X-Shear", RECT_X + RECT_W + 20.0f, RECT_Y + RECT_H + 5.0f);

    // 6. Y-Shear (Quadrant 1)
    glPushMatrix();
    // Applies our custom 4x4 matrix.
    // This skews the shape upwards. The right side moves higher than the left side because its X is higher.
    applyYShear(1.2f);
    drawRectangle(RECT_X, RECT_Y, RECT_W, RECT_H);
    glPopMatrix();
    drawText("Y-Shear", RECT_X + 15.0f, RECT_Y + RECT_H + 55.0f);

    // Forces OpenGL to execute all queued commands immediately.
    glFlush(); 
}

// --- Initialization ---

void init() {
    // Set the background clear color to a light cyan/white
    glClearColor(0.88f, 0.93f, 0.95f, 1.0f);
    
    // Switch to the Projection matrix to set up our camera/viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Reset the matrix to the default identity matrix (1s on the diagonal, 0s elsewhere)
    
    // gluOrtho2D maps coordinates to pixel space. 
    // By using negative to positive values (-300 to 300), we ensure (0,0) is exactly in the middle of the window.
    gluOrtho2D(-ORTHO_X, ORTHO_X, -ORTHO_Y, ORTHO_Y);
    
    // Switch back to the ModelView matrix, which is what we use to move/scale/rotate objects inside the display() function.
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Single buffer (fine for static images), standard RGB colors
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("LAB");
    
    init(); // Call our setup function
    glutDisplayFunc(display); // Tell GLUT to use our display() function for drawing
    
    glutMainLoop(); // Hand control over to the GLUT event loop (keeps the window open)
    return 0;
}