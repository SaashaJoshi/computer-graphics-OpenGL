#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;

int r, xc, yc, sides, t1, t2, angle;
void regular_polygon(void);
void clear_screen(void);

void plotpoint(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x+xc, y+yc);
	glEnd();
}

void clear_screen()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void mouse(GLint button, GLint action, GLint xm, GLint ym)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        xc = xm ;
        yc = 600 - ym;
        clear_screen();
        regular_polygon();
    }
}


void myInit (void)
{
	glClearColor(1, 1, 1, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 840, 0, 600);
}


void regular_polygon()
{
    r = 30;
    sides = 3;

	int x = 0;
	int y = r;
	angle = 360 /sides;
	t1 = x;
	t2 = y;
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i <sides; i++)
    {
        x = r*cos((i*360/sides)*3.141/180);
        y = r*sin((i*360/sides)*3.141/180);
        glVertex2i(x + xc,y + yc);

        t1 = x;
        t2 = y;
    }
    glEnd();
    glFlush();
}

void myDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(1.1);
	glFlush ();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (840, 600);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Translation");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouse);
	myInit ();
	glutMainLoop();
	return 0;

}
