#include <GL/glut.h>
#include <math.h>

#include <iostream>
using namespace std;

int r;
int count = 0;
int width, height;
static int window, menu_id, submenu_id, submenu_id1, submenu_id2, value = 0;
int cx, cy;              // Centre coordinates
int bx, by, c = 0, w, h; // Boundary Point coordinates

void plotpoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plotCircle()
{
    r = sqrt(pow(bx - cx, 2) + pow(by - cy, 2));
    cout << "Radius: " << r;
    int x = 0;
    int y = r;
    float decision = 5 / 4 - r;
    plotpoint(x, y);
    glBegin(GL_POINTS);
    glVertex2i(cx, cy);
    glEnd();
    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2 * x + 1;
        }
        else
        {
            y--;
            x++;
            decision += 2 * (x - y) + 1;
        }
        if (count % 10 == 0)
        {
            plotpoint(x, y);
            plotpoint(x, -y);
            plotpoint(-x, y);
            plotpoint(-x, -y);
            plotpoint(y, x);
            plotpoint(-y, x);
            plotpoint(y, -x);
            plotpoint(-y, -x);
        }
        count++;
    }
}

void plotCircledash()
{

    int flag = 1;
    r = sqrt(pow(bx - cx, 2) + pow(by - cy, 2));
    cout << "Radius: " << r;
    int x = 0;
    int y = r;
    float decision = 5 / 4 - r;
    plotpoint(x, y);
    glBegin(GL_POINTS);
    glVertex2i(cx, cy);
    glEnd();
    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2 * x + 1;
        }
        else
        {
            y--;
            x++;
            decision += 2 * (x - y) + 1;
        }
        if (flag)
        {
            plotpoint(x, y);
            plotpoint(x, -y);
            plotpoint(-x, y);
            plotpoint(-x, -y);
            plotpoint(y, x);
            plotpoint(-y, x);
            plotpoint(y, -x);
            plotpoint(-y, -x);
        }
        count++;
        if (count % 5 == 0)
            flag = !flag;
    }
}
void menu(int num)
{
    if (num == 0)
    {
        glutDestroyWindow(window);
        exit(0);
    }
    else
    {
        value = num;
    }
    glutPostRedisplay();
}

void createMenu(void)
{
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Dotted", 2);
    glutAddMenuEntry("Dashed", 3);
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Properties", submenu_id);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if (c == 0)
        {
            cx = xMouse;
            cy = yMouse;
            cout << "Center: (" << cx - w / 2 << "," << h / 2 - cy << ")\n";
        }

        else if (c == 1)
        {
            bx = xMouse;
            by = yMouse;
            cout << "Point on Boundary: (" << bx - w / 2 << "," << h / 2 - by << ")\n";
            plotCircle();
        }
        c++;
    }
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(1.0f);
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1.0, 1.0);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LINE_STIPPLE);
    if (value == 1)
    {
        glClearColor(1.0, 1.0, 1.0, 0.0);
        return; //glutPostRedisplay();
    }
    else if (value == 2)
    {
        plotCircle();
    }
    else if (value == 3)
    {
        glPushMatrix();
        plotCircledash();
        glPopMatrix();
    }
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Mouse Func");
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    createMenu();
    glutDisplayFunc(display);
    init();
    glutMouseFunc(mousePtPlot);

    glutMainLoop();

    return 0;
}