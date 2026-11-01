#include <GL/glut.h>

void display() {
    // Set background color to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the intersecting lines (axes)
    glColor3f(0.7f, 0.7f, 0.7f); // Light gray
    glBegin(GL_LINES);
        // Horizontal line (X-axis)
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        // Vertical line (Y-axis)
        glVertex2f(0.0f, -100.0f);
        glVertex2f(0.0f, 100.0f);
    glEnd();

    // Draw the small horizontal label lines indicated by the red circles[cite: 2]
    glColor3f(0.4f, 0.5f, 0.8f); // Bluish-gray for the label markers
    glBegin(GL_LINES);
        // Far left line
        glVertex2f(-80.0f, 40.0f);
        glVertex2f(-70.0f, 40.0f);
        
        // Bottom center line
        glVertex2f(5.0f, -5.0f);
        glVertex2f(15.0f, -5.0f);
        
        // Middle right line
        glVertex2f(75.0f, 45.0f);
        glVertex2f(85.0f, 45.0f);
        
        // Top right line
        glVertex2f(70.0f, 75.0f);
        glVertex2f(80.0f, 75.0f);
    glEnd();

    // Draw Triangle 1 (Top-Left Quadrant)
    glColor3f(0.4f, 0.8f, 0.8f); // Cyan outline
    glBegin(GL_LINE_LOOP); 
        glVertex2f(-70.0f, 30.0f);
        glVertex2f(-20.0f, 15.0f);
        glVertex2f(-20.0f, 45.0f);
    glEnd();

    // Draw Triangle 2 (Top-Right, small bottom)
    glColor3f(0.4f, 0.7f, 0.6f); // Green outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(10.0f, 5.0f);
        glVertex2f(40.0f, 5.0f);
        glVertex2f(25.0f, 30.0f);
    glEnd();

    // Draw Triangle 3 (Top-Right, large center)
    glColor3f(0.8f, 0.4f, 0.4f); // Red outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(25.0f, 20.0f);
        glVertex2f(85.0f, 20.0f);
        glVertex2f(55.0f, 70.0f);
    glEnd();

    // Draw Triangle 4 (Top-Right, small top)
    glColor3f(0.3f, 0.5f, 0.9f); // Blue outline
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Triangles and Label Lines");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}