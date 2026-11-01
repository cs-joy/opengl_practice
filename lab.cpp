#include <GL/glut.h>

void display() {
    // 1. Set background color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 2. Draw the intersecting lines (axes)
    glColor3f(0.7f, 0.7f, 0.7f); // Light gray color for lines
    glBegin(GL_LINES);
        // Horizontal line (X-axis)
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        // Vertical line (Y-axis)
        glVertex2f(0.0f, -100.0f);
        glVertex2f(0.0f, 100.0f);
    glEnd();

    // 3. Draw Triangle 1 (Top-Left Quadrant) - Cyan outline
    glColor3f(0.4f, 0.8f, 0.8f);
    glBegin(GL_LINE_LOOP); // GL_LINE_LOOP creates empty wireframe triangles
        glVertex2f(-70.0f, 30.0f);
        glVertex2f(-20.0f, 15.0f);
        glVertex2f(-20.0f, 45.0f);
    glEnd();

    // 4. Draw Triangle 2 (Top-Right, small bottom) - Green outline
    glColor3f(0.4f, 0.7f, 0.6f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(10.0f, 5.0f);
        glVertex2f(40.0f, 5.0f);
        glVertex2f(25.0f, 30.0f);
    glEnd();

    // 5. Draw Triangle 3 (Top-Right, large center) - Red outline
    glColor3f(0.8f, 0.4f, 0.4f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(25.0f, 20.0f);
        glVertex2f(85.0f, 20.0f);
        glVertex2f(55.0f, 70.0f);
    glEnd();

    // 6. Draw Triangle 4 (Top-Right, small top) - Blue outline
    glColor3f(0.3f, 0.5f, 0.9f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(70.0f, 60.0f);
        glVertex2f(95.0f, 60.0f);
        glVertex2f(82.5f, 85.0f);
    glEnd();

    glFlush(); // Render the scene
}

void init() {
    // Setup an orthographic coordinate system spanning from -100 to 100
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0); 
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Setup window size and position
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    
    // Create the window
    glutCreateWindow("Triangles and Lines");
    
    // Initialize projection matrix
    init();
    
    // Register the display callback function
    glutDisplayFunc(display);
    
    // Enter the infinite event-processing loop
    glutMainLoop();
    return 0;
}