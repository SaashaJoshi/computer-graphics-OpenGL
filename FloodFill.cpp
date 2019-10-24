#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
}

void flood_it(int x, int y, float* fillColor, float* ic){
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if(color[0]==ic[0] && color[1]==ic[1] && color[2]==ic[2]){
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
        flood_it(x-1,y,fillColor,ic);
        flood_it(x+1,y,fillColor,ic);
        flood_it(x,y+1,fillColor,ic);
        flood_it(x,y-1,fillColor,ic);
    }
}

void world( int x1, int x2, int y1, int y2)
{    
    int i;
    cout<<"Enter sides of polygon : ";
    cin>>i;
    float R = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float a = (360 / i) * 3.141 / 180;
    cout << "Each angle=" << a;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for (int n = 0; n < i; n++)
    {
        glColor3f(1,0,0);
        glVertex2i(x1 + R * cos(a * n), y1 + R * sin(a * n));
    }
    glEnd();
    glFlush();
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    world(200, 250, 300, 350);
    glFlush();
}
void mouse(int btn, int state, int x, int y){
    y = 480-y;
    if(btn==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            float intCol[] = {1,0,0};
            float color[] = {0,0,1};
            glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,intCol);
            flood_it(x,y,color,intCol);
        }
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Flood Fill");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
