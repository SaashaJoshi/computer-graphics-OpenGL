#include <GL/glut.h>

GLint ww=600, wh=600;
GLint x0, y0, xEnd, yEnd;

inline GLint round(const GLfloat a)
{
	return GLint(a);
}

void Init()
{
	glClearColor(0.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(3.0);
	glLineWidth(5.0);
	glLoadIdentity();
}

void setPixel(GLint x0, GLint y0)
{
	glBegin(GL_POINTS);
	glVertex2i(x0, y0);
	glEnd();
	glFlush();
}

void line_DDA(GLint x0, GLint y0, GLint xEnd, GLint yEnd)
{
	GLint dx=abs(xEnd-x0);
	GLint dy=abs(yEnd-y0);
	GLint lle;
	GLfloat xInc, yInc, x=x0, y=y0;

	if (dx>dy)
		lle=abs(dx);
	else
		lle=abs(dy);

	xInc=GLfloat(dx)/GLfloat(lle);
	yInc=GLfloat(dy)/GLfloat(lle);
	setPixel(round(x), round(y));

	for (int k=1;k<lle;k++)
	{
		x+=xInc;
		y+=yInc;
		setPixel(round(x), round(y));
	}
}

void mouse_click(GLint btn, GLint state, GLint x, GLint y)
{
	int flag=0;
	if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		switch(flag)
		{
			case 0: x0=x;
					y0=wh-y;
					flag=1;
					break;
			case 1: xEnd=x;
					yEnd=wh-y;
					
					flag=0;
					break;
		}
	}
}

void Display()
{
	line_DDA(x0, y0, xEnd, yEnd);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Line DDA");
	Init();
	glutDisplayFunc(Display);
	glutMouseFunc(mouse_click);
	glutMainLoop();
	return 0;
}