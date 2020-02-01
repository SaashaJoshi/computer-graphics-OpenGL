#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

const double PI=3.14;
int click=0;
int frameNumber=0;

struct Point
{
    GLint x;
    GLint y;
};

Point p1, p2;

/*void setPixel(int x, int y, float f[3]){
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}*/

void draw_circle(Point p1, Point p2)
{
    GLfloat xr = p2.x - p1.x;
    GLfloat yr = p2.y - p1.y;

    GLfloat xcenter = p1.x;
    GLfloat ycenter = p1.y;

    float var = pow(xr, 2) + pow(yr, 2);
    float r = pow(var, 0.5);
    float x = 0, y = r;
    float p = 5 / 4 - r;
    glClear(GL_COLOR_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2i(xcenter, ycenter);

    glBegin(GL_POINTS);
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
        glVertex2i(xcenter + x, ycenter + y);
        glVertex2i(xcenter - x, ycenter + y);
        glVertex2i(xcenter + x, ycenter - y);
        glVertex2i(xcenter - x, ycenter - y);

        glVertex2i(xcenter + y, ycenter + x);
        glVertex2i(xcenter - y, ycenter + x);
        glVertex2i(xcenter + y, ycenter - x);
        glVertex2i(xcenter - y, ycenter - x);
    }

    glEnd();
    glFlush();
    glutSwapBuffers();
}

void draw_spokes(Point p1, Point p2){
    GLfloat xr = p2.x - p1.x;
    GLfloat yr = p2.y - p1.y;

    GLfloat xcenter = p1.x;
    GLfloat ycenter = p1.y;

    float var = pow(xr, 2) + pow(yr, 2);
    float r = pow(var, 0.5);

    float a= (360/8)*3.141/180;
    float xi, yi;

    for(int i=0; i<8; i++){
        xi= xcenter + r*cos(a*i);
        yi= ycenter + r*sin(a*i);
        glBegin(GL_LINES);
        glVertex2i(xcenter, ycenter);
        glVertex2i(xi, yi);
        glEnd();
    }
}

/*void draw_spokes(Point p1, Point p2){
    GLfloat xr = p2.x - p1.x;
    GLfloat yr = p2.y - p1.y;

    GLfloat xcenter = p1.x;
    GLfloat ycenter = p1.y;

    float var = pow(xr, 2) + pow(yr, 2);
    float r = pow(var, 0.5);
    //float x = 0, y = r;

    glBegin(GL_LINES);

    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter, ycenter + r);
    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter, ycenter - r);
    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter + r, ycenter);
    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter - r, ycenter);

    //float r2=

    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter + r/2, ycenter + r/2);
    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter - r/2, ycenter - r/2);
    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter + r/2, ycenter - r/2);
    glVertex2d(xcenter, ycenter);
    glVertex2d(xcenter - r/2, ycenter + r/2);

    glEnd();
    glFlush();
}*/

/*void boundary_fill(int x,int y,float fillColor[3],float borderColor[3]){
    float interiorColor[3];
    getPixel(x,y,interiorColor);
    if((interiorColor[0]!=borderColor[0] && (interiorColor[1])!=borderColor[1] && (interiorColor[2])!=borderColor[2]) && (interiorColor[0]!=fillColor[0] && (interiorColor[1])!=fillColor[1] && (interiorColor[2])!=fillColor[2])){
        setPixel(x,y,fillColor);
        boundary_fill(x+1,y,fillColor,borderColor);
        boundary_fill(x-1,y,fillColor,borderColor);
        boundary_fill(x,y+1,fillColor,borderColor);
        boundary_fill(x,y-1,fillColor,borderColor);
    }
}*/

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
            draw_spokes(p1, p2);
        }
        /*else if(click==2){
            boundary_fill(Point p1, f_color);
        }
        else if(click==3){
            glRotatef(frameNumber*30,0,0,1);
        }*/

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
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Circle");
    glutDisplayFunc(display);
    init();
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
