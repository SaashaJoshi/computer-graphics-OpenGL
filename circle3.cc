#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979324
using namespace std;
int x_start, y_start;
int x_end, y_end, c = 0;
int width, height;
void drawScene(void)
{
    float R = sqrt((x_end-x_start)*(x_end-x_start)+(y_end-y_start)*(y_end-y_start)); // Radius of circle.
    float X = x_start; 
    float Y = y_start; 
    int numVertices = 25; 
    float t = 0; 
    int i;
 
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 0.0, 0.0);
    
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < numVertices; ++i)
    {
        glColor3ub(0.0, 0.0, 0.0); 
        glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
        t += 2 * PI / numVertices;
    }
    glEnd();
    
   
    glFlush(); 
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
    glLoadIdentity();
}


void keyInput(unsigned char key, int x, int y)
{
    switch(key) 
    {
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
    glutCreateWindow("square.cpp");
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    setup(); 
    glutMouseFunc(mouse);
    glutDisplayFunc(drawScene); 
    glutReshapeFunc(resize);  
    glutKeyboardFunc(keyInput);
    
    glutMainLoop(); 
    
    return 0;  
}