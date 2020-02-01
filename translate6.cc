#include <GL/glut.h>

#include <stdlib.h>

#include <iostream>

#include <string>

#include <string>

#include <ctype.h>

#include <math.h>

#include <stdio.h>

#include <map>

#include <vector>

using namespace std;



int trans_x,trans_y;

#define pi 2.0*acos(0)









long x_min,x_max,y_min,y_max;





vector <int>x_cor;

vector <int>y_cor;







long draw_line(long x_start , long y_start , long x_end, long y_end)

{



    glBegin(GL_LINES);

    glVertex2f(x_start,y_start); //start points

    glVertex2f(x_end,y_end); // end points

    glEnd();



    return 0;



}





// draw point or pixel by sending cordinate

long  draw_point(long X , long Y)

{



    glBegin(GL_POINTS);

    glVertex2f(X,Y);

    glEnd();



    return 0;



}











int translate(int org_x, int org_y)

{

    int i ,j;

    for(i =0;i<x_cor.size(); ++i)

    {

        x_cor[i] -= org_x;

        y_cor[i] -= org_y;

    }





    for(i=0;i<x_cor.size();++i)

    {

        //draw_point(x_cor[i],y_cor[i]);

    }





    return 0;

}



int scale(int s_x,int s_y)

{

    int i ,j;



    for(i=0;i<x_cor.size();++i)

    {

        x_cor[i] *= s_x;

        y_cor[i] *= s_y;

    }





    return 0;

}



int anti_translate(int org_x , int org_y)

{

    glColor3d(1,0,0);

    int i,j;



    for(i=0;i<x_cor.size();++i)

    {

        x_cor[i] += org_x;

        y_cor[i] += org_y;

    }





    for(i=1;i<x_cor.size();++i)

    {

        draw_line(x_cor[i-1],y_cor[i-1],x_cor[i],y_cor[i]);



    }



    draw_line(x_cor[0],y_cor[0],x_cor[x_cor.size()-1],y_cor[x_cor.size()-1]);



    return 0;

}





int rotate(int angle)

{

    glColor3d(0,1,0);

    int i , j;



    for(i=0;i<x_cor.size();++i)

    {

        double angle_rad = pi / 180.0;

        x_cor[i] = x_cor[i] * cos(angle_rad * angle) - y_cor[i]*sin(angle_rad * angle);

        y_cor[i] = x_cor[i] * sin(angle_rad * angle) + y_cor[i]*cos(angle_rad * angle);

     //   draw_point(x_cor[i] ,y_cor[i]);

    }



    return 0;

}







static void display(void)

{



    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3d(1,1,1); // set pixel color;



     for(i=1;i<x_cor.size();i++){

        draw_line(x_cor[i-1],y_cor[i-1],x_cor[i],y_cor[i]);

    }





    draw_line(x_cor[0],y_cor[0],x_cor[x_cor.size()-1],y_cor[x_cor.size()-1]);



    // for scale the object by any cordinate //

/*



    translate(trans_x,trans_y);



    int s_x = 2 ,s_y = 2;

    scale(s_x,s_y);



    anti_translate(trans_x,trans_y);

*/





    // for rotate the object by any cordinate //





    translate(trans_x,trans_y);



    int angle = 30;

    rotate(angle);



    anti_translate(trans_x,trans_y);







    //rotate_point(30,1,2);







    glutSwapBuffers();

}





/*





4

300 300

350 300

350 350

300 350





3

100 100

150 100

125 150







*/



/* Program entry point */



int main(int argc, char *argv[])

{

    int i,x,y,n;

    glutInit(&argc, argv);

    glutInitWindowSize(640,480);

    glutInitWindowPosition(10,10);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);





    cin>>n;

    for(i=0;i<n;i++){

        cin>>x>>y;

        x_cor.push_back(x);

        y_cor.push_back(y);

    }





    cin>>trans_x>>trans_y;





    glutCreateWindow("TRANSFORMATION");



    glOrtho(0,640,0,480,0,1);

    glutDisplayFunc(display);





    glutMainLoop();

    return EXIT_SUCCESS;

}