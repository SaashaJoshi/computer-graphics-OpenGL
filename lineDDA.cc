#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
int x0,y0,xEnd,yEnd;

void Init(void)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.3,0.4,1.0);
    glPointSize(5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    gluOrtho2D(-100, 100, -100, 100);
}
void readInput()
{
    printf("Enter x0, y0, xEnd, yEnd(resp): ");
    scanf("%i %i %i %i",&x0,&y0,&xEnd,&yEnd);
}

void setPixel(int xcoordinate, int ycoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xcoordinate,ycoordinate);
    glEnd();
}

void lineDDA()
{
    int dx = abs(xEnd-x0);
    int dy = abs(yEnd-y0);
    int steps,k;
    GLfloat xIncrement,yIncrement, x, y;

    if(dx>dy)
        steps = dx;
    else
        steps = dy;

    xIncrement = dx/steps;
    yIncrement = dy/steps;
    x=x0;
    y=y0;
    setPixel(x, y);

    for(k=1;k<steps;k++)
    {
        x+= xIncrement;
        y+= yIncrement;
        setPixel(x, y);
    }

    glFlush();
}


int main(int argc,char *argv[])
{
    readInput();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(50,50);
    glutCreateWindow("DDA Line Algorithum");
    Init();
    glutDisplayFunc(lineDDA);
    glutMainLoop();
    return 0;
}