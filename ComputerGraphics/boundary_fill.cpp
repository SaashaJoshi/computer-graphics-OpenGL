#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

static int menu_id, submenu_id;
float b_color[3]={0.0, 0.0, 0.0};
float f_color[3];
static int value=0;

void setPixel(int x, int y, float f[3]){
	glBegin(GL_POINTS);
	glColor3fv(f);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float p[3]){
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, p);
}

void draw_polygon(int x1, int y1, int x2, int y2){
	glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glEnd();
    
    glFlush();
}

void boundary_fill(int x,int y,float fillColor[3],float borderColor[3]){
    float interiorColor[3];
    getPixel(x,y,interiorColor);
    if((interiorColor[0]!=borderColor[0] && (interiorColor[1])!=borderColor[1] && (interiorColor[2])!=borderColor[2]) && (interiorColor[0]!=fillColor[0] && (interiorColor[1])!=fillColor[1] && (interiorColor[2])!=fillColor[2])){
    	setPixel(x,y,fillColor);
      	boundary_fill(x+1,y,fillColor,borderColor);
        boundary_fill(x-1,y,fillColor,borderColor);
        boundary_fill(x,y+1,fillColor,borderColor);
        boundary_fill(x,y-1,fillColor,borderColor);
    }
}
  
void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        int xi = x;
        int yi = (480-y);
        boundary_fill(xi,yi,f_color,b_color);
    }
}

void menu(int n){
	if(n==0)
		exit(0);
	else 
		value=n;
	glutPostRedisplay();
}

void create_menu(){
	submenu_id=glutCreateMenu(menu);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Blue", 4);
	menu_id=glutCreateMenu(menu);
	glutAddMenuEntry("Clear", 1);
	glutAddSubMenu("Color", submenu_id);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(){
	glViewport(0,0,640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640,0.0,480);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE);

	glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_polygon(300,300,500,500);

	if(value==2){
		float f_color[3]={1.0, 0.0, 0.0};
	}
	else if(value==3){
		float f_color[3]={0.0, 1.0, 0.0};
	}
	else if(value==4){
		float f_color[3]={0.0, 0.0, 1.0};
	}

	glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Boundry Fill");
    create_menu();
    glutDisplayFunc(display);
    init();
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}