#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>
int width, height;
int fig = 0;
float slope;
int c;
int x_beg, y_beg, x_end, y_end, line_x1, line_y1, line_x2, line_y2, x_new, y_new;
using namespace std;

struct code
{
    int above, below, right, left;
};

void get_window(int a, int b, int m, int n);
void fun();

void display();

void plotpoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenham(int xa, int ya, int xb, int yb)
{

    int dx = xb - xa;
    int dy = yb - ya;

    int x = xa, y = ya;

    glBegin(GL_POINTS);
    plotpoint(x - width / 2, height / 2 - y);

    int k;
    if (abs(dx) >= abs(dy))
    {
        int p0 = dx - 2 * dy;
        int p = p0;
        if (xb > xa && yb > ya) // quadrant 1
        {
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x + 1;
                    y = y + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx - 2 * dy;
                }

                else
                {
                    y = y;
                    x = x + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }
            }
        }

        else if (xb < xa && yb < ya) // quadrant 3
        {
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x - 1;
                    y = y;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy + 2 * dx;
                }
            }
        }
        else if (xa > xb && yb > ya) // quadrant 2
        {
            p = -dx - 2 * dy;
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x - 1;
                    y = y + 1;

                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx - 2 * dy;
                }

                else
                {
                    y = y;
                    x = x - 1;

                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }
            }
        }

        else if (xa < xb && yb < ya) // quadrant 4
        {
            for (k = 0; k < abs(dx); k++)
            {
                if (p < 0)
                {
                    x = x + 1;
                    y = y;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx - 2 * dy;
                }
            }
        }
    }

    else if (abs(dy) > abs(dx))
    {
        int p0 = dy - 2 * dx; ///     /////
        int p = p0;
        if (xb > xa && yb > ya) // first quadrant
        {
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x;
                    y = y + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx;
                }

                else
                {
                    y = y + 1;
                    x = x + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx - 2 * dy;
                }
            }
        }

        else if (xa > xb && yb > ya) // second quadrant
        {
            p = 2 * dx + dy;
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x - 1;
                    y = y + 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx + 2 * dy;
                }

                else
                {
                    y = y + 1;
                    x = x;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p + 2 * dx;
                }
            }
        }
        else if (xa > xb && ya > yb) // third quadrant
        {
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x;
                    y = y - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx;
                }

                else
                {
                    y = y - 1;
                    x = x - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx + 2 * dy;
                }
            }
        }

        else if (xb > xa && yb < ya) // fourth quadrant
        {
            p = -2 * dx - dy;
            for (k = 0; k < abs(dy); k++)
            {
                if (p < 0)
                {
                    x = x + 1;
                    y = y - 1;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx - 2 * dy;
                }

                else
                {
                    y = y - 1;
                    x = x;
                    plotpoint(x - width / 2, height / 2 - y);
                    p = p - 2 * dx;
                }
            }
        }
    }
}

code get_code(int a, int b)
{
    code c;

    if (a < x_beg)
    {
        c.left = 1;
        cout << "left" << endl;
    }

    else
        c.left = 0;

    if (a > x_end)

    {
        c.right = 1;
        cout << "right" << endl;
    }
    else
    {
        c.right = 0;
    }
    if (b < y_beg)
    {
        c.below = 1;
        cout << "below" << endl;
    }

    else
        c.below = 0;
    if (b > y_end)
    {
        c.above = 1;
        cout << "above" << endl;
    }

    else
        c.above = 0;
    cout << c.above << c.below << c.right << c.left << endl;

    return c;
}

void intersections(int a, int b, float m, code p)
{
    float C;
    C = b - m * a;

    x_new = a;
    y_new = b;

    if (p.left == 1)
    {
        x_new = x_beg;
        y_new = m * x_beg + C;
    }

    if (p.right == 1)
    {
        x_new = x_end;
        y_new = m * x_end + C;
    }
    if (p.above == 1)
    {

        y_new = y_end;
        x_new = (y_end - C) / m;
    }
    if (p.below == 1)
    {
        x_new = (y_beg - C) / m;
        y_new = y_beg;
    }

    if (a == line_x1)
    {
        line_x1 = x_new;
        line_y1 = y_new;
    }
    else if (a == line_x2)
    {
        line_x2 = x_new;
        line_y2 = y_new;
        fun();
    }
}

void fun()
{
    code point1, point2;
    point1 = get_code(line_x1, line_y1);
    point2 = get_code(line_x2, line_y2);
    cout << point1.above << " " << point1.below << " " << point1.right << " " << point1.left << endl;
    cout << point2.above << " " << point2.below << " " << point2.right << " " << point2.left << endl;
    if (point1.above == 0 && point1.below == 0 && point1.right == 0 && point1.left == 0 && point2.above == 0 && point2.below == 0 && point2.right == 0 && point2.left == 0)

    {
        cout << " line is completely inside" << endl;
        glPointSize(2.0);
        glColor3f(1.0, 1.0, 0.0);
        bresenham(line_x1 + width / 2, height / 2 - line_y1, line_x2 + width / 2, height / 2 - line_y2);
        glColor3f(0.0, 0.0, 0.0);
        glPointSize(1.0);
    }
    else
    {
        code res;
        res.above = point1.above && point2.above;
        res.below = point1.below && point2.below;
        res.right = point1.right && point2.right;
        res.left = point1.left && point2.left;
        if (res.above == 0 && res.below == 0 && res.right == 0 && res.left == 0)
        {
            cout << "partially inside/outside" << endl;
            intersections(line_x1, line_y1, slope, point1);
            intersections(line_x2, line_y2, slope, point2);
            glPointSize(3.0);
            glColor3f(1.0, 1.0, 0.0);
            bresenham(line_x1 + width / 2, height / 2 - line_y1, line_x2 + width / 2, height / 2 - line_y2);
            glColor3f(0.0, 0.0, 0.0);
            glPointSize(1.0);
        }
        else
        {
            cout << "line completely outside" << endl;
        }
    }
}

void mouse(GLint button, GLint action, GLint xM, GLint yM)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        if (c == 0)
        {
            x_beg = xM - width / 2;
            y_beg = height / 2 - yM;
            cout << "point 1: (" << x_beg << "," << y_beg << ")\n";
            plotpoint(x_beg, y_beg);
            c++;
        }
        else if (c == 1)
        {
            x_end = xM - width / 2;
            y_end = height / 2 - yM;
            cout << "point 2: (" << x_end << "," << y_end << ")\n";
            plotpoint(x_end, y_end);
            get_window(x_beg, y_beg, x_end, y_end);

            c++;
        }
        else if (c == 2)
        {
            line_x1 = xM - width / 2;
            line_y1 = height / 2 - yM;
            //cout << "point 1: (" << x_beg << "," <<  y_beg << ")\n";
            plotpoint(line_x1, line_y1);
            c++;
        }
        else if (c == 3)
        {
            line_x2 = xM - width / 2;
            line_y2 = height / 2 - yM;
            //cout << "point 1: (" << x_beg << "," <<  y_beg << ")\n";
            float m, n;
            m = line_y2 - line_y1;
            n = line_x2 - line_x1;
            slope = m / n;
            plotpoint(line_x2, line_y2);
            bresenham(line_x1 + width / 2, height / 2 - line_y1, line_x2 + width / 2, height / 2 - line_y2);

            fun();

            c = 2;
        }
    }
    glFlush();
}

void get_window(int a, int b, int m, int n)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a, b);
    glVertex2f(m, b);
    glVertex2f(m, n);
    glVertex2f(a, n);
    glEnd();
}

void display(void)
{
    glColor3f(0.0, 0.0, 0.0);

    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 50);
	glutInitWindowSize(500,500);
    glutCreateWindow("DropDown");

    width = glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

