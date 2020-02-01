#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
int x_start, y_start;
int x_end, y_end, c = 0;
int width, height;
static int window;
static int menu_id;
static int submenu_id;
static int submenu_id1;
static int submenu_id2;
static int submenu_id3;
static int value = 0;
#define drawOneLine(x1, y1, x2, y2) \
    glBegin(GL_LINES);              \
    glVertex2f((x1), (y1));         \
    glVertex2f((x2), (y2));         \
    glEnd();
void plotpoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plotline(string z = "line"){

    int x1 = x_start - width / 2;
    int x2 = x_end - width / 2;
    int y1 = height / 2 - y_start;
    int y2 = height / 2 - y_end;
    int a =0;
    float dy, dx, step, x, y, k, Xin, Yin;
    dx = x2 - x1;
    dy = y2 - y1;
    if (abs(dx) > abs(dy))
    {
        step = abs(dx);
    }
    else
        step = abs(dy);
    for (int i = 1; i <= step; i = i * 2)
    {
        a = i;
    }
    step = a * 2;

    Xin = dx / step;
    Yin = dy / step;

    x = x1;
    y = y1;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    for (k = 1; k <= step; k++)
    {
        x = x + Xin;
        y = y + Yin;

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }

    glFlush();
}
void plotlineb(string z = "line")
{
    int x1 = x_start - width / 2;
    int x2 = x_end - width / 2;
    int y1 = height / 2 - y_start;
    int y2 = height / 2 - y_end;
    int l = 0, m = 0;
    int dx = x2 - x1;
    int dy = y2 - y1;
    cout << dx << "\t" << dy << endl;
    int n = 0;
    if (abs(dx) > abs(dy))
    {
        n = abs(dx);
        if (y1 > y2)
            l = 1;
        else
            l = -1;
        if (x1 > x2)
            m = -1;
        else
            m = 1;
        int p = 2 * m * dy + l * dx;
        while (n != 0)
        {
            if (p < 0)
            {
                x1 = x1 + m;
                y1 = y1 - ((m + l) / 2);
                p = p + m * 2 * dy + l * dx + m * dx;
            }
            else
            {
                x1 = x1 + m;
                y1 = y1 + ((m - l) / 2);
                p = p + m * 2 * dy + l * dx - m * dx;
            }
            cout << "(" << x1 << "," << y1 << ")" << endl;
            
            plotpoint(x1, y1);
            n--;
        }
        glFlush();
    }
    else
    {
        n = abs(dy);
        if (y1 > y2)
            l = -1;
        else
            l = 1;
        if (x1 > x2)
            m = 1;
        else
            m = -1;
        int p = 2 * l * dx + m * dy;
        while (n != 0)
        {
            if (p < 0)
            {
                y1 = y1 + l;
                x1 = x1 - ((m + l) / 2);
                p = p + 2 * l * dx + l * dy + m * dy;
            }
            else
            {
                y1 = y1 + l;
                x1 = x1 + ((l - m) / 2);
                p = p + 2 * l * dx - l * dy + m * dy;
            }
            cout << "(" << x1 << "," << y1 << ")" << endl;
            plotpoint(x1, y1);
            n--;
        }
        glFlush();
    }
}
void mouse(GLint button, GLint action, GLint xM, GLint yM)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if (c == 0)
        {
            x_start = xM;
            y_start = yM;
            cout << "Starting point: (" << x_start - width / 2 << "," << height / 2 - y_start << ")\n";
            plotpoint(x_start - width / 2, height / 2 - y_start);
            c++;
        }
        else if (c == 1)
        {
            x_end = xM;
            y_end = yM;
            cout << "Ending point: (" << x_end - width / 2 << "," << height / 2 - y_end << ")\n";
            plotpoint(x_end - width / 2, height / 2 - y_end);
            plotline();
            c--;
        }
    }
    glFlush();
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
    glutAddMenuEntry("Dashed-Dotted", 4);
    submenu_id1 = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 5);
    glutAddMenuEntry("Green", 6);
    glutAddMenuEntry("Blue", 7);
    submenu_id2 = glutCreateMenu(menu);
    glutAddMenuEntry("1-size", 8);
    glutAddMenuEntry("3-size", 9);
    glutAddMenuEntry("5-size", 10);
    submenu_id3 = glutCreateMenu(menu);
    glutAddMenuEntry("DDA", 11);
    glutAddMenuEntry("Bresenham", 12);
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Properties", submenu_id);
    glutAddSubMenu("Color", submenu_id1);
    glutAddSubMenu("Thickness", submenu_id2);
    glutAddSubMenu("Algorithm", submenu_id3);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
        glPushMatrix();
        glLineStipple(1, 0x1010); /*  dash/dot/dash  */
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 3)
    {
        glPushMatrix();
        glLineStipple(1, 0xFF00);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 4)
    {
        glPushMatrix();
        // plotline("dashdot");
        glLineStipple(1, 0xF820); /*  dash/dot/dash  */
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 5)
    {
        glPushMatrix();
        glColor3d(1.0, 0.0, 0.0);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 6)
    {
        glPushMatrix();
        glColor3d(0.0, 1.0, 0.0);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 7)
    {
        glPushMatrix();
        glColor3d(0.0, 0.0, 1.0);
        drawOneLine(x_start - width / 2, height / 2 - y_start, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        drawOneLine(x_end - width / 2, height / 2 - y_end, ((x_end + x_start) / 2) - width / 2, height / 2 - ((y_end + y_start) / 2));
        glPopMatrix();
    }
    else if (value == 8)
    {
        glPushMatrix();
        //g-000000000000-0000-p0-00-p0-0-plPointSize(1.0);
        plotlineb();
        glPopMatrix();
    }
    else if (value == 9)
    {
        glPushMatrix();
        glPointSize(3.0);
        plotlineb();
        glPopMatrix();
    }
    else if (value == 10)
    {
        glPushMatrix();
        glPointSize(5.0);
        plotlineb();
        glPopMatrix();
    }
    else if (value == 11)
    {
        glPushMatrix();
        plotline();
        glPopMatrix();
    }
    else if (value == 12)
    {
        glPushMatrix();;
        plotlineb();
        glPopMatrix();
    }
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("DropDown");
    glutInitWindowSize(600, 600);
    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1.0, 1.0);
    createMenu();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}