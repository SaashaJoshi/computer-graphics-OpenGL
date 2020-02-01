#include <iostream>
#include<vector>
// #include "flood_fill.h"
#include <GL/glut.h>
#include <cmath>

using namespace std;

struct GLColor {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

struct Point{
    GLint x;
    GLint y;

    Point(){
        x=0;
        y=0;
    }
    Point(int a, int b){
        x = a;
        y = b;
    }
}point,trans;

struct Line{
    Point s;
    Point e;
    GLfloat slope;
    GLColor color;
}line;

struct Circle{
    Point c;
    GLint r;
    GLColor color;
}circle;

vector<Point> points;
vector<Line> lines;
vector<Circle> circles;

GLColor colors[7] = {
	{0.0f, 0.0f, 0.0f},	// Black
	{1.0f, 0.0f, 0.0f},	// Red
	{0.0f, 1.0f, 0.0f}, // Green
	{0.0f, 0.0f, 1.0f}, // Blue
	{1.0f, 1.0f, 0.0f}, // Yellow
	{1.0f, 0.0f, 1.0f},	// Purple
    {1.0f, 1.0f, 1.0f}  // White
};

int ch=2;
int ind;
Point ps,pe;
float threshold = 10;
string flag;
float theta=0;

GLColor color = colors[0]; // Default: Black

int c=0;
int w,h;

float sx=1.0,sy=1.0;

double radian(int degree){
    return degree*(M_PI/180);
}

void init (char* name)
{
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1000,1000);
    glutCreateWindow(name);
    w=glutGet(GLUT_WINDOW_WIDTH);
    h=glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0,0.4,0.2);
    glMatrixMode (GL_PROJECTION);
    glPointSize(2);
    cout<<w<<" "<<h<<endl;
    glOrtho(-w/2 ,w/2, -h/2, h/2, -1.0, 1.0);

}

void draw_pixel(Point p) {
	// glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
	glColor3f(color.red, color.green, color.blue);
    // cout<<"Drawing pixel"<<endl;
	glBegin(GL_POINTS);
	    glVertex2i((p.x*cos(theta)-p.y*sin(theta)) * sx, (p.x*sin(theta)+p.y*cos(theta)) * sy);
	glEnd();
    glFlush();
}

void display()
{
    
    glPointSize(1);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for(int i=-w/2; i<=w/2; i++)
    {
        glVertex2i(i,0);
    }
    for(int i=-h/2; i<=h/2; i++)
    {
        glVertex2i(0,i);
    }
    glEnd();
    glFlush();
}

void plotline()
{
    int x1 = ps.x + trans.x;
    int x2 = pe.x + trans.x;
    int y1 = ps.y + trans.y;
    int y2 = pe.y + trans.y;

   
    int l=0,m=0;
    int dx=x2-x1;
    int dy=y2-y1;

    line.s = {x1,y1};
    line.e = {x2,y2};
    line.slope = dy/float(dx);
    line.color = color;
    lines.push_back(line);

    int maxi=0;
    if(abs(dx)>abs(dy))
    {
        maxi=abs(dx);
        if(y1>y2)
            l=1;
        else
            l=-1;
        if(x1>x2)
            m=-1;
        else
            m=1;
        int p=2*m*dy+l*dx;
        while(maxi!=0)
        {
            if(p<0)
            {
                x1=x1+m;
                y1=y1-((m+l)/2);
                p=p+m*2*dy+l*dx+m*dx;
            }
            else
            {
                x1=x1+m;
                y1=y1+((m-l)/2);
                p=p+m*2*dy+l*dx-m*dx;
            }
            // cout<<"("<<x1<<","<<y1<<")"<<endl;
            draw_pixel({x1,y1});
            maxi--;
        }
    }
    else
    {
        maxi=abs(dy);
        if(y1>y2)
            l=-1;
        else
            l=1;
        if(x1>x2)
            m=1;
        else
            m=-1;
        int p=2*l*dx+m*dy;
        while(maxi!=0)
        {
            if(p<0)
            {
                y1=y1+l;
                x1=x1-((m+l)/2);
                p=p+2*l*dx+l*dy+m*dy;
            }
            else
            {
                y1=y1+l;
                x1=x1+((l-m)/2);
                p=p+2*l*dx-l*dy+m*dy;
            }
            // cout<<"("<<x1<<","<<y1<<")"<<endl;
            draw_pixel({x1,y1});
            maxi--;
        }
    }
}

void plotCircle(){
    int radius,x,y=0,err=0,m;

    int x1 = ps.x;
    int x2 = pe.x;
    int y1 = ps.y;
    int y2 = pe.y;

    radius = sqrt( pow((x2-x1),2) + pow((y2-y1),2) );

    circle.r = radius;
    circle.c = ps;
    circle.color = color;
    circles.push_back(circle);

    x=radius;
    cout<<"Radius : "<<radius<<endl;

    // p = pat[ch - 1];
   
    while (x >= y)
    {
        glBegin(GL_POINTS);

        // bool m = p & 1;
        // if(m){
            draw_pixel({x1 + x, y1 + y});
            draw_pixel({x1 + y, y1 + x});
            draw_pixel({x1 - y, y1 + x});
            draw_pixel({x1 - x, y1 + y});
            draw_pixel({x1 - x, y1 - y});
            draw_pixel({x1 - y, y1 - x});
            draw_pixel({x1 + y, y1 - x});
            draw_pixel({x1 + x, y1 - y});
        // }
        
        // p = rotr8(p, 1);

        if (err <= 0){
            y += 1;
            err += 2*y + 1;
        }
        
        if (err > 0){
            x -= 1;
            err -= 2*x + 1;
        }
       
    }

}

GLColor getPixelColor(GLint x, GLint y) {
    GLColor color;
    glReadPixels(x+w/2, y+h/2, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(GLint x, GLint y, GLColor color) {
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void floodFill(GLint x, GLint y, GLColor oldColor, GLColor newColor) {
    GLColor color;
    color = getPixelColor(x, y);
    // cout<<" point: ("<<x<<","<<y<<")\n";
    cout<<color.red<<" "<<color.green<<" "<<color.blue<<endl;
    cout<<oldColor.red<<" "<<oldColor.green<<" "<<oldColor.blue<<endl;

    if( x>-w/2 && y>-h/2 && x<w/2 && y<h/2 && color.red== oldColor.red && color.green == oldColor.green && color.blue== oldColor.blue)
    {
        // cout<<"Matched ";
        setPixelColor(x, y, newColor);
        floodFill(x, y-1, oldColor, newColor);
        floodFill(x-1, y, oldColor, newColor);
        floodFill(x, y+1, oldColor, newColor);
        floodFill(x+1, y, oldColor, newColor);
            
    }
    return;
}

int findNearestObject(Point p){
    for(int i=0;i<lines.size();i++){
        line = lines[i];
        Point ps = line.s;
        Point pe = line.e;

        int a = pe.y - ps.y;
        int b = ps.x - pe.x;
        int c = -(a*ps.x + b*ps.y);

        int dist = abs(a*p.x + b*p.y + c)/sqrt(a*a + b*b);

        if(dist<=threshold){
            flag = "line";
            cout<<flag<<" "<<i<<endl;
            return i;
        }
    }

    for(int i=0;i<circles.size();i++){
        circle = circles[i];
        Point c = circle.c;
        GLint r = circle.r;

        int dist = sqrt( pow((c.x-p.x),2) + pow((c.y-p.y),2) );

        if(dist<=r){
            flag = "circle";
            cout<<flag<<" "<<i<<endl;
            return i;
        }
    }
    return -1;
}


void mainMenuHandler(int choice) {
    if(choice==8){
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        lines.clear();
        circles.clear();
        points.clear();
        return;
    }
    ch = choice;
    cout<<"ch="<<ch<<endl;
}

void subMenuHandler(int choice) {
	color = colors[choice];
}

void mousePtPlot (GLint button, GLint action, GLint xMouse, GLint yMouse){
    display();
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        switch (ch)
        {
        case 1:
            // Point
            cout<<"Mouse "<<ch<<endl;
            point.x = xMouse - w/2;
            point.y = h/2 - yMouse;
            draw_pixel(point);
            points.push_back(point);

            cout<<"Points: "<<points.size()<<endl;
            break;
        
        case 2:
            // Line Bresenham
    
            if(c==0){
                ps.x = xMouse-w/2;
                ps.y = h/2-yMouse;
                cout<<"Starting point: ("<<ps.x<<","<<ps.y<<")\n";
                draw_pixel(ps);
                c++;
            }
            else if(c==1){
                pe.x = xMouse-w/2;
                pe.y = h/2-yMouse;
                cout<<"Ending point: ("<<pe.x<<","<<pe.y<<")\n";
                draw_pixel(pe);
                plotline();
                c--;

                cout<<"Lines: "<<lines.size()<<endl;
            }
            break;
        case 3:
            // Circle
            if(c==0){
                ps.x = xMouse-w/2;
                ps.y = h/2-yMouse;
                cout<<"Starting point: ("<<ps.x<<","<<ps.y<<")\n";
                draw_pixel(ps);
                c++;
            }
            else if(c==1){
                pe.x = xMouse-w/2;
                pe.y = h/2-yMouse;
                cout<<"Ending point: ("<<pe.x<<","<<pe.y<<")\n";
                draw_pixel(pe);
                plotCircle();
                c--;
                cout<<"Circles: "<<circles.size()<<endl;
            }
            break;
        case 4:
            // translation
            if(c==0){
                ps.x = xMouse-w/2;
                ps.y = h/2-yMouse;
                cout<<"selection point: ("<<ps.x<<","<<ps.y<<")\n";
                ind = findNearestObject(ps);
                if(ind>=0)
                    c++;
            }
    
            else if(c==1){
                pe.x = xMouse-w/2;
                pe.y = h/2-yMouse;
                cout<<"Ending point: ("<<pe.x<<","<<pe.y<<")\n";

                if(flag=="line"){
                    
                    Line line = lines[ind];

                    int tx = pe.x - ps.x;
                    int ty = pe.y - ps.y; 

                    // Remove old line
                    ps = line.s;
                    pe = line.e;
                    color = colors[6];

                    trans = {0,0};

                    lines.erase(lines.begin()+ind);
                    plotline();
                    lines.pop_back();  

                    //draw old line
                    trans.x = tx;
                    trans.y = ty;
                    
                    color = line.color;

                    plotline();
                }
                else if(flag=="circle"){
                    Circle circle = circles[ind];
                    Point c = circle.c;
                    GLint r = circle.r;

                    Point new_c = pe;

                    // Remove Old circle
                    ps = c;
                    pe.x = c.x + r;
                    pe.y = c.y;
                    color = colors[6];

                    trans = {0,0};

                    circles.erase(circles.begin()+ind);
                    plotCircle();
                    circles.pop_back();
                    
                    // draw new circle
                    ps = new_c;
                    pe.x = ps.x + r;
                    pe.y = ps.y;
                    color = circle.color;

                    plotCircle();
                }    
                c--;
            }
            break;
        case 5:
            {
            // Flood fill
            int sx = xMouse - w/2;
            int sy = h/2 - yMouse;
            cout<<" point: ("<<sx<<","<<sy<<")\n";

            GLColor oldColor = getPixelColor(sx,sy);
            
            floodFill(sx,sy,oldColor,color);
            
            glFlush();
            }
            break;
        case 6:
            // scaling
            if(c==0){
                point.x = xMouse-w/2;
                point.y = h/2-yMouse;
                cout<<"selection point: ("<<point.x<<","<<point.y<<")\n";
                ind = findNearestObject(point);
                if(ind>=0)
                    c++;
            }
            else if(c==1){
                ps.x = xMouse-w/2;
                ps.y = h/2-yMouse;
                cout<<"Ending point: ("<<ps.x<<","<<ps.y<<")\n";
                c++;
            }
    
            else if(c==2){
                pe.x = xMouse-w/2;
                pe.y = h/2-yMouse;
                cout<<"Ending point: ("<<pe.x<<","<<pe.y<<")\n";

                float sx_ = abs(pe.x - ps.x)/100.0 +1;
                float sy_ = abs(pe.y - ps.y)/100.0 + 1;

                if(flag=="line"){
                    
                    Line line = lines[ind];

                    // Remove old line
                    ps = line.s;
                    pe = line.e;
                    color = colors[6];

                    trans = {0,0};

                    lines.erase(lines.begin()+ind);
                    plotline();
                    lines.pop_back();  

                    //draw new line
                    // ps.x *= sx;
                    // pe.x *= sx;

                    // ps.y *= sy;
                    // pe.y *= sy;
                    sx = sx_;
                    sy = sy_;

                    
                    color = line.color;

                    plotline();
                    
                }
                else if(flag=="circle"){
                    
                    Circle circle = circles[ind];
                    Point c = circle.c;
                    GLint r = circle.r;

                    // Remove Old circle
                    ps = c;
                    pe.x = c.x + r;
                    pe.y = c.y;
                    color = colors[6];

                    trans = {0,0};

                    circles.erase(circles.begin()+ind);
                    plotCircle();
                    circles.pop_back();
                    
                    // draw new circle
                    sx = sx_;
                    sy = sy_;
                    color = circle.color;

                    plotCircle();
                }    
                sx=1;
                sy=1;
                c-=2;
            }
            break;   
        case 7:
            // rotation
            if(c==0){
                ps.x = xMouse-w/2;
                ps.y = h/2-yMouse;
                cout<<"selection point: ("<<ps.x<<","<<ps.y<<")\n";
                ind = findNearestObject(ps);
                if(ind>=0)
                    c++;
            }
    
            else if(c==1){
                pe.x = xMouse-w/2;
                pe.y = h/2-yMouse;
                cout<<"Ending point: ("<<pe.x<<","<<pe.y<<")\n";
                float m2 = (pe.y - ps.y)/float(pe.x - ps.x);
                

                if(flag=="line"){
                    
                    Line line = lines[ind];
                    float m1 = line.slope;

                    // Remove old line
                    ps = line.s;
                    pe = line.e;
                    color = colors[6];

                    lines.erase(lines.begin()+ind);
                    plotline();
                    lines.pop_back(); 

                    // draw new line
                    float tan_theta = (m2-m1)/float(1+m1*m2);
                    theta = atan(radian(30));
                    color = line.color;

                    plotline();
                }
               
                c--;
                theta=0;
            }
            break;
        }
    }
 }

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	
    char name[] = "Menus";
	init(name);
    // display();
    glutDisplayFunc(display);

    glutMouseFunc(mousePtPlot);

	int subMenu = glutCreateMenu(subMenuHandler);
	glutAddMenuEntry("Default", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("Purple", 5);

	glutCreateMenu(mainMenuHandler);
	glutAddSubMenu("Change Color", subMenu);
	glutAddMenuEntry("Pixel", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Circle", 3);
	glutAddMenuEntry("Translate", 4);
	//glutAddMenuEntry("Color Fill", 5);
    glutAddMenuEntry("Scaling",6);
    glutAddMenuEntry("Rotation",7);
    glutAddMenuEntry("Clear Canvas",8);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
    
	glutMainLoop();

	return 0;
}
