#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

//int count=0;
static int menu_id, submenu_id, submenu_id1, submenu_id2;
static int value=0;
int click=0;

struct Point
{
    GLint x;
    GLint y;
};

Point p1, p2;

void draw_circle(Point p1, Point p2)
{
	int count=0;
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
    glVertex2i(xcenter, ycenter);

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

        if(count%10==0){
        	glVertex2i(xcenter + x, ycenter + y);
        	glVertex2i(xcenter - x, ycenter + y);
	        glVertex2i(xcenter + x, ycenter - y);
	        glVertex2i(xcenter - x, ycenter - y);

	        glVertex2i(xcenter + y, ycenter + x);
	        glVertex2i(xcenter - y, ycenter + x);
	        glVertex2i(xcenter + y, ycenter - x);
	        glVertex2i(xcenter - y, ycenter - x);	
        }   
        count++;
    }

    glEnd();
    glFlush();
    glutSwapBuffers();
}

void draw_circle_dash(Point p1, Point p2)
{
	int flag=1;
	int count=0;
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
    glVertex2i(xcenter, ycenter);

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

        if(flag){
        	glVertex2i(xcenter + x, ycenter + y);
        	glVertex2i(xcenter - x, ycenter + y);
	        glVertex2i(xcenter + x, ycenter - y);
	        glVertex2i(xcenter - x, ycenter - y);

	        glVertex2i(xcenter + y, ycenter + x);
	        glVertex2i(xcenter - y, ycenter + x);
	        glVertex2i(xcenter + y, ycenter - x);
	        glVertex2i(xcenter - y, ycenter - x);	
        }   
        count++;

        if(count%5==0)
        	flag=!flag;
    }

    glEnd();
    glFlush();
    glutSwapBuffers();
}

void menu(int n){
	if(n==0){
		//glutDestroyWindow(window);
		exit(0);
	}
	else
		value=n;
	glutPostRedisplay();
}

void create_menu(){
	submenu_id=glutCreateMenu(menu);
	glutAddMenuEntry("Dotted", 2);
	glutAddMenuEntry("Dashed", 3);
	menu_id=glutCreateMenu(menu);
	glutAddMenuEntry("Clear", 1);
	glutAddSubMenu("Properties", submenu_id);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    	if(click==0){
    		p1.x = x;
	        p1.y = 480 - y;
    	}
    	else if(click==1){
    		p2.x = x;
        	p2.y = 480 - y;
    	    draw_circle(p1, p2);
    	}
        click++;
    }
    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(2.0f);
    gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE);

	if(value==1){
		glClearColor(1.0, 1.0, 1.0, 0.0);
		return;
	}
	else if(value==2){
		draw_circle(p1, p2);
	}
	else if(value==3){
		glPushMatrix();
		draw_circle_dash(p1, p2);
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
    glutCreateWindow("Circle");
    create_menu();
    glutDisplayFunc(display);
    init();
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}