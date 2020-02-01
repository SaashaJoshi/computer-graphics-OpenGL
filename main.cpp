#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

struct Point {
	GLfloat x;
	GLfloat y;
};

bool selection=false,composition=false,pivot_choose=false;
int selected=0;

Point pivot;

void mymousefunc(int,int,int,int);
void drag1(int,int);
void show_every(void);

int num = 0;


class line {
public:
    Point start, ending;
    int oldx=0,oldy=0;
    int xdiff=0,ydiff=0;


};



class polygon {
public:
    int oldx=0,oldy=0;
    int xdiff=0,ydiff=0;
    int sides;
    int temp=0;
    bool draw_poly=false,select = false,translation=false;
    Point p[12],center;

    void draw_polygon(){
    getsides();
    this->draw_poly =true;
    }

    void mix(int x,int y,float theta){
        int i = 0;
        while(i!=sides){
            p[i].x = p[i].x - x;
            p[i].y = p[i].y - y;
            i++;
        }
        rotat(theta);
        i = 0;
        while(i!=sides){
            p[i].x = p[i].x + x;
            p[i].y = p[i].y + y;
            i++;
        }
        show_every();
        glFlush();
        composition = false;
    }

    void poly_mouse_func(int x, int y){
            if(temp!=sides){
                p[temp].x = x;
                p[temp].y = 600-y;
                glColor3f(1.0f, 0.0f, 0.0f);
                glBegin(GL_POINTS);
                    glVertex2d(p[temp].x,p[temp].y);
                glEnd();
                glFlush();
                temp++;
                if(temp==sides){
                    draw_poly = false;
                    this->show();
                    int i=0;
                    while(i!=sides){
                        center.x += p[i].x;
                        center.y += p[i].y;
                        i++;
                    }
                    center.x = center.x/sides;
                    center.y = center.y/sides;
                    num++;
                }
            }
    }
    void translate(){
        glutMotionFunc(drag1);
        }
    void shear(float xs,float ys){
        int i=0;
        int xo,yo;
        while(i!=sides){
            xo = p[i].x;
            yo=p[i].y;
            p[i].x = xo + xs*yo;
            p[i].y = yo + ys*xo;
            i++;
        }
        show_every();
        glFlush();
    }
    void scale(float xscale, float yscale){
//        glClear(GL_COLOR_BUFFER_BIT);
        int i=0;
        while(i!=sides){
            p[i].x = xscale* p[i].x;
            p[i].y = yscale* p[i].y;
            i++;
        }
        if(!composition){
            show_every();
        }
        glFlush();
    }
    void show()
    {
                glBegin(GL_POLYGON);
                glColor3f(1.0f, 0.0f, 0.0f);
                int i = 0;
                while(i!=sides){
                    glVertex2d(p[i].x,p[i].y);
                    i++;
                }
                glEnd();
                glFlush();
            }
    void rotat(float theta){
    int i = 0;
    while(i!=sides){
        p[i].x = p[i].x*cos(theta)+p[i].y*sin(theta);
        p[i].y = p[i].y*cos(theta)-p[i].x*sin(theta);
        i++;
    }
    if(!composition){
            show_every();
        }
    glFlush();
    }
    void drag(int x,int y){
        glClear(GL_COLOR_BUFFER_BIT);
        if(translation){
        xdiff = x - oldx;
        ydiff = y - oldy;
        }
        else{
            xdiff=0,ydiff=0;
        }
        int i = 0;
        while(i!=sides){
            p[i].x = p[i].x + xdiff;
            p[i].y = p[i].y - ydiff;
            i++;
        }
        if(!composition){
            show_every();
        }
        glEnd();
        glFlush();
        translation = true;
        oldx = x;
        oldy = y;
        }
private:
    void getsides(){
        cout<<"\nEnter the no of sides of the polygon (MAX 12)  ";
        cin>>sides;
        }

};
polygon poly[10];
//bool draw_poly = false,draw_line=false,poly=false,line=false;
//Point p1,p2,p[12];
//int translate_custom=0,sides = 0,temp=0;

void show_every(){
    int i=0;
    while(i!=num){
        poly[i].show();
        i++;
    }
}

void drag1(int x, int y){
    poly[selected].drag(x,y);
    }

void init2() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(1.0f);
	gluOrtho2D(0.0f, 1000.0f, 0.0f, 600.0f);
}
void mymousefunc(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && poly[num].draw_poly){
        poly[num].poly_mouse_func(x,y);
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && selection){
            int temp = (poly[0].center.x - x)*(poly[0].center.x - x) + (poly[0].center.y + y-600)*(poly[0].center.y + y-600);
            int val=0;
        for(int i =0;i<=num;i++){
                poly[i].select = false;
            if((poly[i].center.x-x)*(poly[i].center.x-x) + (poly[i].center.y+y-600)*(poly[i].center.y+y-600)<temp){
                val=i;
                temp = (poly[i].center.x-x)*(poly[i].center.x-x) + (poly[i].center.y+y-600)*(poly[i].center.y+y-600);
            }
        }
        selected = val;
        poly[val].select = true;
        selection = false;
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && poly[selected].translation){
        poly[selected].translation = false;
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && pivot_choose){
        pivot.x= x;
        pivot.y = 600-y;
        pivot_choose = false;
    }
    }

//void mymousefunc(int button, int state, int x, int y){
//    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && draw_poly){
//        line = false;
//            if(temp!=sides){
//                p[temp].x = x;
//                p[temp].y = 480-y;
//                glBegin(GL_POINTS);
//                    glVertex2d(p[temp].x,p[temp].y);
//                glEnd();
//                temp++;
//            }
//            else{
//                glBegin(GL_POLYGON);
//                glColor3f(1.0f, 0.0f, 0.0f);
//                int i = 0;
//                while(i!=sides){
//                    glVertex2d(p[i].x,p[i].y);
//                    i++;
//                }
//                glEnd();
//                glFlush();
//                draw_poly=false;
//                poly=true;
//            }
//    }
//    else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && draw_line){
//        if(temp == 2){
//            poly = false;
//            p[0].x = x;
//            p[0].y = 480-y;
//            temp =1;
//        }
//        else if(temp == 1){
//            p[1].x = x;
//            p[1].y = 480-y;
//            glBegin(GL_LINES);
//            glColor3f(1.0f, 0.0f, 0.0f);
//            glVertex2i(p[0].x,p[0].y);
//            glVertex2i(p[1].x,p[1].y);
//            glEnd();
//            glFlush();
//            draw_line = false;
//            line = true;
//        }
//    }
//}

//int oldx=0,oldy=0;
//int xdiff=0,ydiff=0;
//bool translate = false;

//    void drag (int x,int y){
//        glClear(GL_COLOR_BUFFER_BIT);
//        if(translate){
//        xdiff = x - oldx;
//        ydiff = y - oldy;
//        }
//        else{
//            xdiff=0,ydiff=0;
//        }
//        int i = 0;
//        if(poly){
//            glBegin(GL_POLYGON);
//        }
//        else if(line){
//            glBegin(GL_LINES);
//        }
//        glColor3f(0.0f, 0.0f, 1.0f);
//        while(i!=sides){
//            p[i].x = p[i].x + xdiff;
//            p[i].y = p[i].y - ydiff;
//            glVertex2d(p[i].x,p[i].y);
//            i++;
//        }
//        glEnd();
//        glFlush();
//        translate = true;
//        oldx = x;
//        oldy = y;
//    }
void Gomenu(int val){
    if(val==1){
        poly[selected].translate();
    }
    else if(val==2){
        poly[num].draw_polygon();
    }
    else if(val==3){
        //temp =2;
        //sides=2;
       // draw_line = true;
    }
    else if(val==4){
        cout<<"Enter the value of theta to be rotated:\ntheta: ";
        float theta;
        cin>>theta;
        poly[selected].rotat(theta);
    }
    else if(val==5){
        cout<<"Enter x and y Scale factors:\n xscale: ";
        float xscale,yscale;
        cin>>xscale;
        cout<<"yscale: ";
        cin>>yscale;
        poly[selected].scale(xscale,yscale);
    }
    else if(val==6){
        selection = true;
    }
    else if(val==7){
        cout<<"Enter the no of rotations to be performed: ";
        int i;
        float temp,theta=0;
        cin>>i;
        while(i!=0){
            cin>>temp;
            theta+=temp;
            i--;
        }
        poly[selected].rotat(theta);
    }
    else if(val==8){
        cout<<"Enter the no of scalings to be performed: ";
        int i;
        float x,y,xs=1,ys=1;
        cin>>i;
        while(i!=0){
            cout<<"\nxscale= ";
            cin>>x;
            cout<<"\nyscale= ";
            cin>>y;
            xs *= x;
            ys*= y;
            i--;
        }
        poly[selected].scale(xs,ys);
    }
    else if(val==9){
        cout<<"Enter the amount of rotation i.e. angle theta: ";
        float theta;
        cin>>theta;
        composition = true;
        pivot_choose = true;
        poly[selected].mix(pivot.x,pivot.y,theta);
        composition = false;
    }
    else if(val==10){
        float xshear,yshear;
        cout<<"\nEnter the shear value of x: ";
        cin>>xshear;
        cout<<"Enter the shear value of y: ";
        cin>>yshear;
        poly[selected].shear(xshear,yshear);
    }
    glutPostRedisplay();
}

void display(void) {}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(1000,600);
	glutCreateWindow("2D-Transformations");
	int sub1 = glutCreateMenu(Gomenu);
        glutAddMenuEntry("Polygon",2);
        glutAddMenuEntry("Line",3);
	int sub2 = glutCreateMenu(Gomenu);
        glutAddMenuEntry("Translation",1);
        glutAddMenuEntry("Rotation",4);
        glutAddMenuEntry("Scaling",5);
    int sub3 = glutCreateMenu(Gomenu);
        glutAddMenuEntry("Succesive Rotation",7);
        glutAddMenuEntry("Succesive Scaling",8);
        glutAddMenuEntry("Rotation w.r.t pivot",9);
        glutAddMenuEntry("Shear",10);
	glutCreateMenu(Gomenu);
        glutAddSubMenu("Shape",sub1);
        glutAddSubMenu("Basic",sub2);
        glutAddSubMenu("Composite",sub3);
        glutAddMenuEntry("Select",6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mymousefunc);
	glutDisplayFunc(display);
	init2();
	glutMainLoop();
	return 0;
}
