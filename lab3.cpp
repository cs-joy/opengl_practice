#include <GL/glut.h>
#include <string.h>

// Helper function to render text on the screen
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

void display() {
    // Set background color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the intersecting lines (axes) in black
    glColor3f(0.0f, 0.0f, 0.0f); 
    glBegin(GL_LINES);
        // Horizontal line (X-axis)
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        // Vertical line (Y-axis)
        glVertex2f(0.0f, -100.0f);
        glVertex2f(0.0f, 100.0f);
    glEnd();

    // Axis Labels
    drawText("X", 95.0f, 3.0f);
    drawText("Y", 3.0f, 95.0f);

    // 1. Draw Left Triangle (Floated)
    glColor3f(0.2f, 0.7f, 0.2f); // Green
    glBegin(GL_LINE_LOOP); 
        glVertex2f(-70.0f, 20.0f);
        glVertex2f(-20.0f, 5.0f);
        glVertex2f(-20.0f, 35.0f);
    glEnd();
    drawText("Floated", -55.0f, 40.0f);

    // 2. Draw Original Triangle (Bottom Left of Positive Quadrant)
    glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray / Black
    glBegin(GL_LINE_LOOP);
        glVertex2f(10.0f, 10.0f);
        glVertex2f(40.0f, 10.0f);
        glVertex2f(25.0f, 35.0f);
    glEnd();
    drawText("Original", 10.0f, 2.0f);

    // 3. Draw Scaled Triangle (Center of Positive Quadrant)
    glColor3f(0.7f, 0.2f, 0.2f); // Red
    glBegin(GL_LINE_LOOP);
        glVertex2f(25.0f, 25.0f);
        glVertex2f(85.0f, 25.0f);
        glVertex2f(55.0f, 75.0f);
    glEnd();
    drawText("Scaled", 75.0f, 50.0f);

    // 4. Draw Translated Triangle (Top Right of Positive Quadrant)
    glColor3f(0.2f, 0.2f, 0.7f); // Blue
    glBegin(GL_LINE_LOOP);
        glVertex2f(65.0f, 60.0f);
        glVertex2f(95.0f, 60.0f);
        glVertex2f(80.0f, 85.0f);
    glEnd();
    drawText("Translated", 65.0f, 90.0f);

    glFlush(); // Render the scene
}

void init() {
    // Setup an orthographic coordinate system spanning from -100 to 100
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Implementation and Analysis of 2D Geometric Translation, Rotation, and Scaling");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}