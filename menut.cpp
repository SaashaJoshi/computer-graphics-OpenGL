#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
int sx,sy;
int ex,ey,c=0,scale,angle;
int r=0;
int w,h,k=0,nx,ny,ox,oy,a,b;
int n;
int arr[500][2];

void drag(){
glColor3f(0.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glColor3f(1.0,1.0,1.0);
for(int i=0;i<k;i++){
glVertex2i(arr[i][0]-ox+nx,arr[i][1]-oy+ny);
}
glEnd();
//glFlush();
}

void display() {
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glBegin(GL_POINTS);
for(int i=-w/2; i<=w/2; i++){
glVertex2i(i,0);
}
for(int i=-h/2; i<=h/2; i++){
glVertex2i(0,i);
}
glEnd();
glFlush();
}

void drawPolygon(void)
{
   // float R = sqrt((ex-sx)*(x_end-x_start)+(y_end-y_start)*(y_end-y_start)); 
    
    float x1,y1;
    cout<<"Enter number of sides:";
    cin>> n;

    float a= (360/n)*3.141/180;
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);

    for(int i=0; i<n ; i++)
{
	x1= sx+r*cos(a*i);
	arr[k][0]=x1;
	y1=sy+r*sin(a*i);
	arr[k][1]=y1;
	k++;	
   
        glVertex2i(x1, y1);
       
}
    glEnd(); 
    glFlush();
}




void rotate(){
float ang=(float)(3.14/180)*angle;

glBegin(GL_LINE_LOOP);
glColor3f(0.0,1.0,0.0);
for(int i=0;i<k;i++){
//cout<<"h"<<i<<" ";

glVertex2i((arr[i][0]-sx)*cos(ang)-(arr[i][1]-sy)*sin(ang)+sx,(arr[i][0]-sx)*sin(ang)+(arr[i][1]-sy)*cos(ang)+sy);

}
glEnd();
glFlush();
}

void scale_fun(){
glBegin(GL_LINE_LOOP);
glColor3f(1.0,1.0,1.0);
for(int i=0;i<k;i++){

glVertex2i((arr[i][0]-sx)*scale+sx,(arr[i][1]-sy)*scale+sy);

}
glEnd();
glFlush();
}

void mousePtPlot (GLint button, GLint action, GLint xMouse, GLint yMouse)
{
if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
{
if(c==0){
sx=xMouse-w/2;
sy=h/2-yMouse;
cout<<"Center: ("<<sx-w/2<<","<<h/2-sy<<")\n";
c++;
}
else if(c==1){
ex=xMouse-w/2;
ey=h/2-yMouse;
cout<<"other point: ("<<ex-w/2<<","<<h/2-ey<<")\n";
r=sqrt((ex-sx)*(ex-sx)+(ey-sy)*(ey-sy));
drawPolygon();
c++;
cout<<"enter if u want to drag,scale,or rotate: \n 2 for drag\n 3 for scale\n 4 rotate\n";
int op;
cin>>op;
// c=op;
if(op==3){
cout<<"Enter the value of scaling: ";
cin>>scale;
scale_fun();
c=0;
}
else if(op==4){
cout<<"Enter the value of angle: ";
cin>>angle;
rotate();
c=0;
}
}
else if(c==2){
//c++;
cout<<c<<endl;
ox=xMouse-w/2;
oy=h/2-yMouse;
if((ox-sx)*(ox-sx)+(oy-sy)*(oy-sy)<=r*r){
c++;
}
}
else if(c==3){
c=c-3;
nx=xMouse-w/2;
ny=h/2-yMouse;
drag();
}
}
glFlush();
}

void init ()
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glMatrixMode (GL_PROJECTION);
cout<<w<<" "<<h<<endl;
glOrtho(-w/2 ,w/2, -h/2, h/2, -1.0, 1.0);
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitWindowPosition(0, 0);
glutInitWindowSize (500, 500);
glutCreateWindow(" Test");
w=glutGet(GLUT_WINDOW_WIDTH);
h=glutGet(GLUT_WINDOW_HEIGHT);
init();
glutDisplayFunc(display);
glFlush();
glutMouseFunc (mousePtPlot);
glutMainLoop();
return 0;
}
