// #include <GL/glut.h>
// #include <string.h>

// // Function to render bitmap text labels
// void drawText(float x, float y, const char* string) {
//     glRasterPos2f(x, y);
//     for (int i = 0; i < strlen(string); i++) {
//         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
//     }
// }

// void display() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Draw Coordinate Axes
//     glColor3f(0.4f, 0.4f, 0.4f);
//     glLineWidth(2.0f);
//     glBegin(GL_LINES);
//     // X-axis
//     glVertex2f(-100.0f, 0.0f);
//     glVertex2f(100.0f, 0.0f);
//     // Y-axis
//     glVertex2f(0.0f, -100.0f);
//     glVertex2f(0.0f, 100.0f);
//     glEnd();

//     glLineWidth(2.0f);

//     // 1. Original Shape (Dark Gray)
//     glColor3f(0.2f, 0.2f, 0.2f);
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(10.0f, 5.0f);
//     glVertex2f(40.0f, 5.0f);
//     glVertex2f(40.0f, 25.0f);
//     glVertex2f(10.0f, 25.0f);
//     glEnd();
//     drawText(10.0f, 1.0f, "Original");

//     // 2. Reflected about Y-axis (Red - Left Quadrant)
//     glColor3f(0.6f, 0.3f, 0.3f);
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(-40.0f, 5.0f);
//     glVertex2f(-10.0f, 5.0f);
//     glVertex2f(-10.0f, 25.0f);
//     glVertex2f(-40.0f, 25.0f);
//     glEnd();

//     // 3. Reflected about X-axis (Blue - Bottom Quadrant)
//     glColor3f(0.3f, 0.4f, 0.8f);
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(10.0f, -25.0f);
//     glVertex2f(40.0f, -25.0f);
//     glVertex2f(40.0f, -5.0f);
//     glVertex2f(10.0f, -5.0f);
//     glEnd();
//     drawText(10.0f, -32.0f, "Reflected about X");

//     // 4. X-Shear (Green)
//     // Transformation Formula: x' = x + shx * y, y' = y
//     float shx = 1.5f;
//     glColor3f(0.3f, 0.7f, 0.4f);
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(10.0f + shx * 5.0f, 5.0f);
//     glVertex2f(40.0f + shx * 5.0f, 5.0f);
//     glVertex2f(40.0f + shx * 25.0f, 25.0f);
//     glVertex2f(10.0f + shx * 25.0f, 25.0f);
//     glEnd();
//     drawText(65.0f, 28.0f, "X-Shear");

//     // 5. Y-Shear (Purple)
//     // Transformation Formula: x' = x, y' = y + shy * x
//     float shy = 1.0f;
//     glColor3f(0.5f, 0.3f, 0.7f);
//     glBegin(GL_LINE_LOOP);
//     glVertex2f(10.0f, 5.0f + shy * 10.0f);
//     glVertex2f(40.0f, 5.0f + shy * 40.0f);
//     glVertex2f(40.0f, 25.0f + shy * 40.0f);
//     glVertex2f(10.0f, 25.0f + shy * 10.0f);
//     glEnd();
//     drawText(45.0f, 70.0f, "Y-Shear");

//     glFlush();
// }

// void init() {
//     // Soft cyan background matching the screen photo
//     glClearColor(0.82f, 0.90f, 0.89f, 1.0f);
    
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
    
//     // Setting up an Orthographic 2D projection scaled to fit all the shapes
//     gluOrtho2D(-60.0, 100.0, -50.0, 90.0);
// }

// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(800, 600);
//     glutInitWindowPosition(100, 100);
//     glutCreateWindow("2D Transformations - Reflections and Shears");
    
//     init();
//     glutDisplayFunc(display);
//     glutMainLoop();
    
//     return 0;
// }

#include <GL/glut.h>
#include <string.h>

// Function to render bitmap text labels
void drawText(float x, float y, const char* string) {
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(string); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Coordinate Axes
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // X-axis
    glVertex2f(-100.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    // Y-axis
    glVertex2f(0.0f, -100.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();

    glLineWidth(2.0f);

    // 1. Original Shape (Dark Gray)
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10.0f, 5.0f);
    glVertex2f(40.0f, 5.0f);
    glVertex2f(40.0f, 25.0f);
    glVertex2f(10.0f, 25.0f);
    glEnd();
    drawText(10.0f, 1.0f, "Original");

    // 2. Reflected about Y-axis (Red - Left Quadrant)
    glColor3f(0.6f, 0.3f, 0.3f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-40.0f, 5.0f);
    glVertex2f(-10.0f, 5.0f);
    glVertex2f(-10.0f, 25.0f);
    glVertex2f(-40.0f, 25.0f);
    glEnd();
    // Added text label for the red rectangle
    drawText(-40.0f, 1.0f, "Reflected about Y");

    // 3. Reflected about X-axis (Blue - Bottom Quadrant)
    glColor3f(0.3f, 0.4f, 0.8f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10.0f, -25.0f);
    glVertex2f(40.0f, -25.0f);
    glVertex2f(40.0f, -5.0f);
    glVertex2f(10.0f, -5.0f);
    glEnd();
    drawText(10.0f, -32.0f, "Reflected about X");

    // 4. X-Shear (Green)
    // Transformation Formula: x' = x + shx * y, y' = y
    float shx = 1.5f;
    glColor3f(0.3f, 0.7f, 0.4f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10.0f + shx * 5.0f, 5.0f);
    glVertex2f(40.0f + shx * 5.0f, 5.0f);
    glVertex2f(40.0f + shx * 25.0f, 25.0f);
    glVertex2f(10.0f + shx * 25.0f, 25.0f);
    glEnd();
    drawText(65.0f, 28.0f, "X-Shear");

    // 5. Y-Shear (Purple)
    // Transformation Formula: x' = x, y' = y + shy * x
    float shy = 1.0f;
    glColor3f(0.5f, 0.3f, 0.7f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10.0f, 5.0f + shy * 10.0f);
    glVertex2f(40.0f, 5.0f + shy * 40.0f);
    glVertex2f(40.0f, 25.0f + shy * 40.0f);
    glVertex2f(10.0f, 25.0f + shy * 10.0f);
    glEnd();
    drawText(45.0f, 70.0f, "Y-Shear");

    glFlush();
}

void init() {
    // Soft cyan background
    glClearColor(0.82f, 0.90f, 0.89f, 1.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Setting up an Orthographic 2D projection scaled to fit all the shapes
    gluOrtho2D(-60.0, 100.0, -50.0, 90.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations - Reflections and Shears");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
