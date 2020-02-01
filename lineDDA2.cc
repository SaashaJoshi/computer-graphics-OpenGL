#include <string.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#define ROUND(x)((int)(x+0.5))

struct Point
{
    GLint x;
    GLint y;
};

struct Color
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

int Height =650, Width=650;
int startX,startY;
static Point vertex [1];
static int pt=0;
Color fillcolor;
void myMouse(int button, int state, int x, int y);

void drawline(double X1,double Y1, double X2, double Y2)
{
    float x,y,dx,dy,length;
    int i;
    
    dx=abs(X2-X1);
    dy=abs(Y2-Y1);
    if(dx>=dy)
        length=dx;
    else
        length=dy;
    dx=(X2-X1)/length;
    dy=(Y2-Y1)/length;
    x=X1;
    y=Y1;
    i=1;
    while(i<=length)
    {
        glColor3f(1.0,1.0,0.0);
        glBegin(GL_POINTS);
        
        glVertex2i(ROUND(x),ROUND(y));
        glEnd();
        glFlush();
        x=x+dx;
        y=y+dy;
        i=i+1;     
    }
    glFlush();
}

void display(void)
{
    char string[]="Click to set points and make a line.";
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    /*
    glRasterPos2f(10,600);
    int len,i;
    len=(int)strlen(string);
    for(i=0;i<len;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,string[i]);
    }
    */
    glFlush();
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,650.0,0.0,650.0);
    
}
void myMouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(pt==0)
        {
            vertex[pt].x=x;
            vertex[pt].y=Height-y;
            startX=x;
            startY=Height-y;
            pt++;
        }
    else
        {
            drawline(vertex[0].x,vertex[0].y,x,Height-y);
            vertex[0].x=x;
            vertex[0].y=Height-y;
        }    
    }
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
    glutInitWindowSize(650,650);
    glutInitWindowPosition(100,100);
    glutCreateWindow("simple DDA");
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    myinit();
    glutMainLoop();
    return 0;
}