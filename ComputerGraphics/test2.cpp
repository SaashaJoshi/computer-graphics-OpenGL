#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979324
using namespace std;
int x_start, y_start;
int x_end, y_end, c = 0;
int width, height;
int count =0;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}
// Drawing (display) routine.
void drawScene(void)
{
    float R = sqrt((x_end-x_start)*(x_end-x_start)+(y_end-y_start)*(y_end-y_start)); 
    float X = x_start; 
    float Y = y_start;
    int numVertices = 25; 
    float t = 0; 
    int i;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    
    
    float xcenter = x_start;
    float ycenter = y_start;

    float x = 0, y = R;
    float p = 5 / 4 - R;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    while (x <= y)
    {
        x++;
        if (p < 0)
        {
            p += 2 * (x + 1) + 1;
        }
        else
        {
            y--;
            p += 2 * (x + 1) + 1 - 2 * (y - 1);
        }
        glVertex2i(xcenter + x, ycenter + y);
        glVertex2i(xcenter - x, ycenter + y);
        glVertex2i(xcenter + x, ycenter - y);
        glVertex2i(xcenter - x, ycenter - y);

        glVertex2i(xcenter + y, ycenter + x);
        glVertex2i(xcenter - y, ycenter + x);
        glVertex2i(xcenter + y, ycenter - x);
        glVertex2i(xcenter - y, ycenter - x);

    }
glEnd();
 float a= (360/8)*3.141/180;
float xi, yi;
  for(int i=0; i<8; i++)
{
	xi= xcenter+R*cos(a*i);
	yi=ycenter+R*sin(a*i);
	glBegin(GL_LINES);
	glVertex2i(xcenter, ycenter);
	glVertex2i(xi, yi);

    glEnd();
}
   // glFlush();
}

void mouse(GLint button, GLint action, GLint xM, GLint yM)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if (c == 0)
        {
            x_start = xM -width/2;
            y_start = height/2- yM;
            cout << "Starting point: (" << x_start << "," << y_start << ")\n";
            c++;
        }
        else if (c == 1)
        {
            x_end = xM - width/2;
            y_end = height/2-yM;
            cout << "Ending point: (" << x_end << "," <<  y_end << ")\n";
            drawScene();
            c--;
        }
    }
    glFlush();
}


void setup(void) 
{
    glClearColor(1.0, 1.0, 1.0, 0.0); 
}




void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    display();
    glLoadIdentity();
}


void keyInput(unsigned char key, int x, int y)
{
    switch(key) 
    {
            // Press escape to exit.
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv) 
{  
  
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("circle.cpp");
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    setup(); 
    glutDisplayFunc(display);
    glFlush();
    glutMouseFunc(mouse);
     
    glutReshapeFunc(resize);  
    glutKeyboardFunc(keyInput);
    
    glutMainLoop(); 
    
    return 0;  
}

