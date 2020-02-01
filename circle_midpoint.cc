#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

struct Point
{
    GLint x;
    GLint y;
};

Point p1, p2;

void draw_dda(Point p1, Point p2)
{
    GLfloat xr = p2.x - p1.x;
    GLfloat yr = p2.y - p1.y;

    GLfloat xcenter = p1.x;
    GLfloat ycenter = p1.y;

    float var = pow(xr, 2) + pow(yr, 2);
    float r = pow(var, 0.5);
    float x = 0, y = r;
    float p = 5 / 4 - r;
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
    glFlush();
    glutSwapBuffers();
}

void myMouseFunc(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        p1.x = x;
        p1.y = 480 - y;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        p2.x = x;
        p2.y = 480 - y;
        draw_dda(p1, p2);
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(2.0f);
    gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}

void display(void) {}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Mouse Func");
    glutDisplayFunc(display);
    init();
    glutMouseFunc(myMouseFunc);
    glutMainLoop();

    return 0;
}
