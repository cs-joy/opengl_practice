#include<GL/glut.h>
float x=0.0f;
float y=0.0f;
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0f,0.0f,0.0f);
glBegin(GL_QUADS);
glVertex2f(x-0.21f,y-0.11f);
glVertex2f(x+0.21f,y-0.11f);
glVertex2f(x+0.21f,y+0.11f);
glVertex2f(x-0.21f,y+0.11f);
glEnd();
glColor3f(0.0f,0.0f,0.0f);
glBegin(GL_QUADS);
glVertex2f(x-0.20f,y-0.10f);
glVertex2f(x+0.20f,y-0.10f);
glVertex2f(x+0.20f,y+0.10f);
glVertex2f(x-0.20f,y+0.10f);
glEnd();
glFlush();
}
void specialKeys(int key,int mouseX,int mouseY)
{
switch(key)
{
case GLUT_KEY_UP:y+=0.05f;break;
case GLUT_KEY_DOWN:y-=0.05f;break;
case GLUT_KEY_LEFT:x-=0.05f;break;
case GLUT_KEY_RIGHT:x+=0.05f;break;
}
glutPostRedisplay();
}
void init()
{
glClearColor(0.0f,0.0f,0.0f,1.0f);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-1,1,-1,1);
}
int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutInitWindowPosition(100,100);
glutCreateWindow("Thin Border Rectangle");
init();
glutDisplayFunc(display);
glutSpecialFunc(specialKeys);
glutMainLoop();
return 0;
}