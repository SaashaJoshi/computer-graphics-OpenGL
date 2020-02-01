#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;
struct point{
GLint x;
GLint y;};

int rectangle = 0;
point r1,r2;
int draw_line = 0;
point l1,l2;
bool show_orig = false;

void line_clip(){
    int xmin = min(r1.x,r2.x);
    int xmax = max(r1.x,r2.x);
    int ymin = min(r1.y,r2.y);
    int ymax = max(r1.y,r2.y);
    float dx = l2.x - l1.x;
    float dy = l2.y - l1.y;
    bool out=false;
    float p[4],q[4];

    p[0] = -dx;
    p[1] = dx;
    p[2] = -dy;
    p[3] = dy;
    q[0] = -(xmin-l1.x);
    q[1] = (xmax-l1.x);
    q[2] = -(ymin-l1.y);
    q[3] = (ymax-l1.y);
    float umin =0, umax=1;
    for(int i=0;i<4;i++){
        if(p[i]<0){
            float u = q[i]/p[i];
            if(u>umax){
                    out = true;
                    break;}
            else{
                if(u>umin){
                    umin = u;
                }
            }
        }
        else if(p[i]>0){
            float u = q[i]/p[i];
            if(u<umin){
                    out = true;
                    break;}
            else if(u<umax){
                umax=u;
            }
        }
        else if(p[i]==0){
            if(q[i]<0){
                    out=true;
                    break;}
        }
    }
    if(umin>umax||out){}
    else{
        umax = min(umax,1.0f);
        umin = max(umin,0.0f);
        //glColor3f(0.0f,0.0f,0.0f);
        glBegin(GL_LINES);
        glVertex2d(l1.x+umax*dx,l1.y+umax*dy);
        glVertex2d(l1.x+umin*dx,l1.y+umin*dy);
        glEnd();
    }
}

void myMouseFunc(int button, int state, int x, int y)
{
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (rectangle!=2) ) {
            if(rectangle==0){
                r1.x = x;
                r1.y = 480 - y;
                rectangle++;
            }
            else if(rectangle==1){
                r2.x = x;
                r2.y = 480 - y;
                //glColor3f(0.0,0.0,0.0);
                glBegin(GL_LINES);
                glVertex2d(r1.x,r1.y);
                glVertex2d(r2.x,r1.y);
                glVertex2d(r2.x,r1.y);
                glVertex2d(r2.x,r2.y);
                glVertex2d(r2.x,r2.y);
                glVertex2d(r1.x,r2.y);
                glVertex2d(r1.x,r2.y);
                glVertex2d(r1.x,r1.y);
                glEnd();
                glFlush();
                rectangle++;
            }
            }
            else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (draw_line) ){
                if(draw_line==1){
                    l1.x = x;
                    l1.y = 480 - y;
                    draw_line++;
                }
                else if(draw_line==2){
                    l2.x = x;
                    l2.y = 480-y;
                    if(show_orig){
                        glColor3f(0.0,0.0,1.0);
                        glBegin(GL_LINES);
                        glVertex2d(l1.x,l1.y);
                        glVertex2d(l2.x,l2.y);
                        glEnd();
                        glFlush();
                    }
                    draw_line = 0;
                    line_clip();
                    glFlush();
                }
            }
        //
}

void myDisplay(void){

	glPointSize(1.0);}

void init2() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    rectangle = 0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
	}

void Gomenu(int val){
    if(val==1){
        draw_line =1;
    }
    // else if(val==2){
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     rectangle = 0;
    // }
    // else if(val==3){
    //     show_orig =!show_orig;
    // }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Line_Clipping");
	glutCreateMenu(Gomenu);
    glutAddMenuEntry("Draw Line",1);
    //glutAddMenuEntry("New Window",2);
    //glutAddMenuEntry("Toogle Origignal Line On/OFF",3);
	glutDisplayFunc(myDisplay);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(myMouseFunc);
	init2();
	glutMainLoop();
    return 0;
}
