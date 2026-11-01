#include <GL/glut.h>
#include <string.h>

/*
 * HELPER FUNCTION: Text Rendering
 * This function handles drawing strings to the OpenGL window.
 * - text: The character array (string) to be displayed.
 * - x, y: The Cartesian coordinates where the text will begin rendering.
 */
void drawText(const char* text, float x, float y) {
    // glRasterPos2f sets the current raster position for pixel operations.
    // In our -100 to 100 orthographic coordinate system, this positions the starting point of the text.
    glRasterPos2f(x, y);
    
    // Calculate the length of the string to loop through each character
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        // glutBitmapCharacter renders a single character at the current raster position.
        // It automatically advances the raster position to the right after drawing each letter, 
        // preventing the need to manually calculate the X offset for the next character.
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

void display() {
    // 1. Clear the screen
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to solid white (R=1.0, G=1.0, B=1.0, Alpha=1.0)
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer with the white background

    // 2. Draw the Cartesian Axes
    glColor3f(0.0f, 0.0f, 0.0f); // Set current drawing color to Black
    glBegin(GL_LINES); // GL_LINES treats each pair of vertices as an independent line segment
        // X-axis: spans horizontally from the far left (-100, 0) to far right (100, 0)
        glVertex2f(-100.0f, 0.0f);
        glVertex2f(100.0f, 0.0f);
        
        // Y-axis: spans vertically from the bottom (0, -100) to top (0, 100)
        glVertex2f(0.0f, -100.0f);
        glVertex2f(0.0f, 100.0f);
    glEnd();

    // Add labels for the axes at their extremities
    drawText("X", 95.0f, 3.0f);
    drawText("Y", 3.0f, 95.0f);

    // 3. Draw Shapes (Transformations) using GL_LINE_LOOP
    // GL_LINE_LOOP connects a series of vertices in order, and automatically 
    // draws a final line from the last vertex back to the first, creating a closed hollow polygon.

    // A. Left Triangle (Demonstrating a "Floated" or arbitrary starting state)
    glColor3f(0.2f, 0.7f, 0.2f); // Set color to Green
    glBegin(GL_LINE_LOOP); 
        glVertex2f(-70.0f, 20.0f); // Top-left vertex
        glVertex2f(-20.0f, 5.0f);  // Bottom-right vertex
        glVertex2f(-20.0f, 35.0f); // Top-right vertex
    glEnd();
    drawText("Floated", -55.0f, 40.0f); // Positioned above the triangle

    // B. Original Triangle (Base Reference Shape)
    glColor3f(0.2f, 0.2f, 0.2f); // Set color to Dark Gray
    glBegin(GL_LINE_LOOP);
        glVertex2f(10.0f, 10.0f); // Bottom-left vertex
        glVertex2f(40.0f, 10.0f); // Bottom-right vertex
        glVertex2f(25.0f, 35.0f); // Top peak vertex
    glEnd();
    drawText("Original", 10.0f, 2.0f); // Positioned below the triangle

    // C. Scaled Triangle (Enlarged Shape)
    glColor3f(0.7f, 0.2f, 0.2f); // Set color to Red
    glBegin(GL_LINE_LOOP);
        // Compared to the Original, the distances between vertices are multiplied, 
        // making the shape larger while shifting its center slightly.
        glVertex2f(25.0f, 25.0f); 
        glVertex2f(85.0f, 25.0f); 
        glVertex2f(55.0f, 75.0f); 
    glEnd();
    drawText("Scaled", 75.0f, 50.0f);

    // D. Translated Triangle (Shifted Shape)
    glColor3f(0.2f, 0.2f, 0.7f); // Set color to Blue
    glBegin(GL_LINE_LOOP);
        // Maintains the exact same geometric proportions as the Original triangle, 
        // but every vertex is shifted +55 on the X-axis and +50 on the Y-axis.
        glVertex2f(65.0f, 60.0f); 
        glVertex2f(95.0f, 60.0f);
        glVertex2f(80.0f, 85.0f);
    glEnd();
    drawText("Translated", 65.0f, 90.0f);

    // Force execution of OpenGL commands in finite time
    glFlush(); 
}

/*
 * INITIALIZATION: Coordinate System and Projection
 */
void init() {
    // Select the projection matrix stack to configure viewing volume
    glMatrixMode(GL_PROJECTION); 
    
    // Reset the projection matrix to the identity matrix (clears previous transformations)
    glLoadIdentity(); 
    
    // gluOrtho2D defines a 2D orthographic projection matrix.
    // Parameters: (left, right, bottom, top)
    // This maps the 800x600 window to a logical Cartesian grid from -100.0 to +100.0 on both axes.
    // The physical center of the window becomes (0,0).
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0); 
}

int main(int argc, char** argv) {
    // Initialize the GLUT library and parse command-line arguments
    glutInit(&argc, argv);
    
    // Set the display mode to Single Buffer (no background rendering) and RGB color mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Define the actual pixel dimensions of the application window (Width, Height)
    glutInitWindowSize(800, 600);
    
    // Set the initial screen location of the window's top-left corner on the monitor
    glutInitWindowPosition(100, 100);
    
    // Create the window with a descriptive title
    glutCreateWindow("Lab Report: 2D Transformations & Coordinate Systems");
    
    // Call the custom initialization function for the coordinate system
    init();
    
    // Register the display callback function (called whenever the window needs to be redrawn)
    glutDisplayFunc(display);
    
    // Enter the GLUT event processing loop, waiting for user interactions or system events
    glutMainLoop();
    
    return 0;
}