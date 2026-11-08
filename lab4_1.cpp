#include <GL/glut.h>

// Helper function to draw a rotated wireframe rectangle
void drawWireframeRect(float cx, float cy, float width, float height, float angle) {
    glPushMatrix(); // Save the current matrix state
    
    // Move to the center of the shape, rotate, and draw
    glTranslatef(cx, cy, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f); 

    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    glBegin(GL_LINE_LOOP);
        glVertex2f(-halfWidth, -halfHeight); // Bottom-left
        glVertex2f(halfWidth, -halfHeight);  // Bottom-right
        glVertex2f(halfWidth, halfHeight);   // Top-right
        glVertex2f(-halfWidth, halfHeight);  // Top-left
    glEnd();

    glPopMatrix(); // Restore the matrix state
}

void display() {
    // White background to match the whiteboard
    glClear(GL_COLOR_BUFFER_BIT);

    // Black marker lines
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.5f); // Slightly thicker line to mimic the marker

    // 1. Top-left rectangle (axis-aligned)
    drawWireframeRect(30.0f, 55.0f, 18.0f, 12.0f, 0.0f);

    // 2. Top-right rectangle (axis-aligned, smaller/taller)
    drawWireframeRect(60.0f, 55.0f, 10.0f, 12.0f, 0.0f);

    // 3. Bottom-left small square (rotated ~45 degrees, positioned below the first shape)
    drawWireframeRect(35.0f, 32.0f, 14.0f, 14.0f, 40.0f);

    // 4. Bottom-right large rectangle/square (rotated ~45 degrees, positioned below the second shape)
    drawWireframeRect(70.0f, 25.0f, 24.0f, 24.0f, 40.0f);

    glutSwapBuffers();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Set up a 2D orthographic viewing region (X: 0 to 100, Y: 0 to 75)
    // This roughly matches a 4:3 aspect ratio landscape view.
    gluOrtho2D(0.0, 100.0, 0.0, 75.0);
    
    glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    // Double buffering for smoother rendering
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    // Set window size and title
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rectangle shape");

    init();

    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Start the main loop
    glutMainLoop();
    return 0;
}