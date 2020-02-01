#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979324
using namespace std;
int x_start, y_start;
int x_end, y_end, c = 0;

int width, height;
int count = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glFlush();
}

void ellipseMidpoint(float xc, float yc, float rx, float ry)
{
    float rxSq = rx * rx;
    float rySq = ry * ry;
    float x = 0, y = ry, p;
    float px = 0, py = 2 * rxSq * y;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    display();
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glEnd();
    p = rySq - (rxSq * ry) + (0.25 * rxSq);
    glBegin(GL_POINTS);
    while (px < py)
    {
        x++;
        px = px + 2 * rySq;
        if (p < 0)
            p = p + rySq + px;
        else
        {
            y--;
            py = py - 2 * rxSq;
            p = p + rySq + px - py;
        }
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
    }
    glEnd();

    p = rySq * (x + 0.5) * (x + 0.5) + rxSq * (y - 1) * (y - 1) - rxSq * rySq;
    glBegin(GL_POINTS);
    while (y > 0)
    {
        y--;
        py = py - 2 * rxSq;
        if (p > 0)
            p = p + rxSq - py;
        else
        {
            x++;
            px = px + 2 * rySq;
            p = p + rxSq - py + px;
        }
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
    }
    glEnd();
}

void mouse(GLint button, GLint action, GLint xM, GLint yM)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if (c == 0)
        {
            x_start = xM - width / 2;
            y_start = height / 2 - yM;
            cout << "Starting point: (" << x_start << "," << y_start << ")\n";
            c++;
        }
        else if (c == 1)
        {
            x_end = xM - width / 2;
            y_end = height / 2 - yM;
            cout << "Ending point: (" << x_end << "," << y_end << ")\n";
            ellipseMidpoint(x_start, y_start, x_end - x_start, y_end - y_start);
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
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    display();
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
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
    glutCreateWindow("Ellipse");
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