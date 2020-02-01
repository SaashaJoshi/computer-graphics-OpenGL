#include <stdio.h>
#include <math.h>
#include <iostream>
#include <math.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<vector>
using namespace std;

int pntX1, pntY1, choice = 0, edges;
vector<int> pntX;
vector<int> pntY;
int transX, transY;
double scaleX, scaleY;
double angle, angleRad;
char reflectionAxis, shearingAxis;
int shearingX, shearingY;

struct Points
{
    float x,y;
    Points() { x = 0.0; y = 0.0; }

    Points(float _x, float _y){
        x=_x;
        y=_y;
    }
};

class Utils{
public:
    Points mouse(int x,int y);
};

Points Utils::mouse(int x, int y)
{
    int windowWidth = 400, windowHeight = 400;
    return Points(float(x)/windowWidth, 1.0 - float(y)/windowHeight);
}


class Line:public Utils{
public:
    Points line_pts[2];
    Line(){
        line_pts[0]=Points(0.5,0.5);
        line_pts[1] = Points(0.7,0.7);
    }
    void draw(Line* line){
        int i;
        glColor3f(0.2, 0.2, 0.2);
        glBegin(GL_LINES);
            glVertex2f(line->line_pts[0].x, line->line_pts[0].y);
            glVertex2f(line->line_pts[1].x, line->line_pts[1].y);
        glEnd();
        i = 0;
        glColor3f(0.2, 0.2, 0.2);
        glBegin(GL_POINTS);
            glVertex2f(line->line_pts[0].x, line->line_pts[0].y);
            glVertex2f(line->line_pts[1].x, line->line_pts[1].y);
        glEnd();
    }
    Line* drag(Line *line, Points *mouse)
    {
        line->line_pts[0].x = mouse->x - 0.1;
        line->line_pts[0].y = mouse->y - 0.1;
        line->line_pts[1].x = mouse->x + 0.1;
        line->line_pts[1].y = mouse->y + 0.1;

        return line;
    }
};


class Square:public Utils
{
public:
    Points square_pts[5];
    Square(){
        square_pts[0] = Points(0.2,0.2);
        square_pts[1] = Points(0.4,0.2);
        square_pts[2] = Points(0.4,0.4);
        square_pts[3] = Points(0.2,0.4);
    };

    void draw(Square *sqr)
    {
        int i;
        glColor3f(0.88, 0.21, 0.0);
        glBegin(GL_POLYGON);
        for (i = 0; i < 3; ++i)
        {
            glVertex2f(sqr->square_pts[i].x, sqr->square_pts[i].y);
        }
        glEnd();
        i = 0;

        glColor3f(0.88, 0.21, 0.0);
        glBegin(GL_POINTS);
        for (i = 0; i < 3; ++i)
        {
            glVertex2f(sqr->square_pts[i].x, sqr->square_pts[i].y);
        }
        glEnd();
    }

    Square* drag(Square *sqr, Points *mouse)
    {
        sqr->square_pts[0].x = mouse->x - 0.1;
        sqr->square_pts[0].y = mouse->y - 0.1;
        sqr->square_pts[1].x = mouse->x + 0.1;
        sqr->square_pts[1].y = mouse->y - 0.1;

        sqr->square_pts[3].x = mouse->x - 0.1;
        sqr->square_pts[3].y = mouse->y + 0.1;

        sqr->square_pts[2].x = mouse->x + 0.1;
        sqr->square_pts[2].y = mouse->y + 0.1;

        return sqr;
    }
};

Square* sqr = new Square;
Line* line=new Line;
void display() {
   // glClear(GL_COLOR_BUFFER_BIT);
    line->draw(line);
    sqr->draw(sqr);
    glFlush();

}

// drag function
void drag (int x, int y)
{
    Points mousePt1 = sqr->mouse(x,y);
    //create pointer to window point coordinates
    Points* mouse1 = &mousePt1;

    // if the mouse is within the square
     if (mouse1->x > sqr->square_pts[0].x && mouse1->y > sqr->square_pts[0].y)
     {
        if (mouse1->x < sqr->square_pts[2].x && mouse1->y < sqr->square_pts[2].y)
        {
            // then drag by chaning square coordinates relative to mouse
            sqr->drag(sqr,mouse1);
           // glutPostRedisplay();
        }
    }

    Points mousePt = line->mouse(x,y);
    Points* mouse = &mousePt;
    if (mouse->x > line->line_pts[0].x && mouse->y > line->line_pts[0].y)
     {
    line->drag(line,mouse);}
    glutPostRedisplay();
}


double round(double d)
{
return floor(d + 0.5);
}

void drawPolygon()
{
glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 0.0);
for (int i = 0; i < edges; i++)
{
glVertex2i(pntX[i], pntY[i]);
}
glEnd();
}


void drawPolygonTrans(int x, int y)
{
glBegin(GL_POLYGON);
glColor3f(0.0, 1.0, 0.0);
for (int i = 0; i < edges; i++)
{
glVertex2i(pntX[i] + x, pntY[i] + y);
}
glEnd();
}

void drawPolygonScale(double x, double y)
{
glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 1.0);
for (int i = 0; i < edges; i++)
{
glVertex2i(round(pntX[i] * x), round(pntY[i] * y));
}
glEnd();
}

void drawPolygonRotation(double angleRad)
{
glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 1.0);
for (int i = 0; i < edges; i++)
{
glVertex2i(round((pntX[i] * cos(angleRad)) - (pntY[i] * sin(angleRad))), round((pntX[i] * sin(angleRad)) + (pntY[i] * cos(angleRad))));
}
glEnd();
}

void drawPolygonMirrorReflection(char reflectionAxis)
{
glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 1.0);

if (reflectionAxis == 'x' || reflectionAxis == 'X')
{
for (int i = 0; i < edges; i++)
{
glVertex2i(round(pntX[i]), round(pntY[i] * -1));

}
}
else if (reflectionAxis == 'y' || reflectionAxis == 'Y')
{
for (int i = 0; i < edges; i++)
{
glVertex2i(round(pntX[i] * -1), round(pntY[i]));
}
}
glEnd();
}

void drawPolygonShearing()
{
glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 1.0);

if (shearingAxis == 'x' || shearingAxis == 'X')
{
glVertex2i(pntX[0], pntY[0]);

glVertex2i(pntX[1] + shearingX, pntY[1]);
glVertex2i(pntX[2] + shearingX, pntY[2]);

glVertex2i(pntX[3], pntY[3]);
}
else if (shearingAxis == 'y' || shearingAxis == 'Y')
{
glVertex2i(pntX[0], pntY[0]);
glVertex2i(pntX[1], pntY[1]);

glVertex2i(pntX[2], pntY[2] + shearingY);
glVertex2i(pntX[3], pntY[3] + shearingY);
}
glEnd();
}

void Initialize() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   // glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
   gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}

void myInit(void)
{
glClearColor(1.0, 1.0, 1.0, 0.0);
glColor3f(0.0f, 0.0f, 0.0f);
glPointSize(4.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}


void myDisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0, 0.0, 0.0);

if (choice == 1)
{
        /*line->draw(line);
        sqr->draw(sqr);
        glFlush();*/
}
else if (choice == 2)
{
drawPolygon();
drawPolygonScale(scaleX, scaleY);
}
else if (choice == 3)
{
drawPolygon();
drawPolygonRotation(angleRad);
}
else if (choice == 4)
{
drawPolygon();
drawPolygonMirrorReflection(reflectionAxis);
}
else if (choice == 5)
{
drawPolygon();
drawPolygonShearing();
}

glFlush();
}

int main(int argc, char** argv)
{
cout << "Enter choice:\n" << endl;
cout << "1. Translation" << endl;
cout << "2. Scaling" << endl;
cout << "3. Rotation" << endl;
cout << "4. Mirror Reflection" << endl;
cout << "5. Shearing" << endl;
cout << "6. Exit" << endl;

cin >> choice;

if (choice == 6 ) {
return 0;
}
  if(choice!=1){
cout << "\n\nFor Polygon:\n" << endl;

cout << "Enter no of edges: "; cin >> edges;
for (int i = 0; i < edges; i++)
{
cout << "Enter co-ordinates for vertex  " << i + 1 << " : "; cin >> pntX1 >> pntY1;
pntX.push_back(pntX1);
pntY.push_back(pntY1);
}

/*if (choice == 1)
{
cout << "Enter the translation factor for X and Y: "; cin >> transX >> transY;
}*/
if (choice == 2)
{
cout << "Enter the scaling factor for X and Y: "; cin >> scaleX >> scaleY;
}
else if (choice == 3)
{
cout << "Enter the angle for rotation: "; cin >> angle;
angleRad = angle * 3.1416 / 180;
}
else if (choice == 4)
{
cout << "Enter reflection axis ( x or y ): "; cin >> reflectionAxis;
}
else if (choice == 5)
{
cout << "Enter reflection axis ( x or y ): "; cin >> shearingAxis;
if (shearingAxis == 'x' || shearingAxis == 'X')
{
cout << "Enter the shearing factor for X: "; cin >> shearingX;
}
else
{
cout << "Enter the shearing factor for Y: "; cin >> shearingY;
}
}
    }
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
if(choice==1){
   glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Transformations");


    glutMotionFunc(drag);

    Initialize();
    glutDisplayFunc(display);
Initialize();}
else{
            glutInitWindowSize(640, 480);
glutInitWindowPosition(100, 150);
glutCreateWindow("Transformations");
glutDisplayFunc(myDisplay);
myInit();}

//glutDisplayFunc(myDisplay);
glutMainLoop();
return 0;
}