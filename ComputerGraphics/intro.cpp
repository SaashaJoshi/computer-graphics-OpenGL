#include <GL/glut.h>
#include <iostream>
using namespace std;

void display(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	//Set Background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);			//Clear background color buffer

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();
	glFlush();
}

void resize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);

}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutCreateWindow("Intro");
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;
}

