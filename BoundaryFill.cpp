#include <GL/glut.h>
#include <cmath>
#include <iostream>
#define PI 3.14159265358979324
using namespace std;
 
int ww = 500, wh = 500, i;
float fillCol[3] = {0.9, 0.0, 0.0};
float borderCol[3] = {0.0, 0.0, 0.0};

void setPixel(int pointx, int pointy, float f[3])
{
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float pixels[3])
{
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

void drawPolygon(int x1, int y1, int x2, int y2)
{
    cout<<"Enter sides of polygon : ";
    cin>>i;
    glColor3f(0.0, 0.0, 0.0);
    float R = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float a = (360 / i) * 3.141 / 180;
    cout << "Each angle=" << a;

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int n = 0; n < i; n++)
    {
        glVertex2i(x1 + R * cos(a * n), y1 + R * sin(a * n));
    }
    glEnd();
    glFlush();
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(200, 250, 250, 350);
    glFlush();
}

void boundaryFill4(int x, int y, float fillColor[3], float borderColor[3])
{
    float interiorColor[3];
    getPixel(x, y, interiorColor);
    if ((interiorColor[0] != borderColor[0] && (interiorColor[1]) != borderColor[1] && (interiorColor[2]) != borderColor[2]) && 
    (interiorColor[0] != fillColor[0] && (interiorColor[1]) != fillColor[1] && (interiorColor[2]) != fillColor[2]))
    {
        setPixel(x, y, fillColor);
        boundaryFill4(x + 1, y, fillColor, borderColor);
        boundaryFill4(x - 1, y, fillColor, borderColor);
        boundaryFill4(x, y + 1, fillColor, borderColor);
        boundaryFill4(x, y - 1, fillColor, borderColor);
    }
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int xi = x;
        int yi = (wh - y);
        boundaryFill4(xi, yi, fillCol, borderCol);
    }
}

void myinit()
{
    glViewport(0, 0, ww, wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bountry-Fill-Recursive");
    glutDisplayFunc(display);
    myinit();
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
