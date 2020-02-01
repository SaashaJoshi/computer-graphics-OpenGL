#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

#define SIZE 500

void instructions ();
void gfxinit ();
void display (void);
void colorMenu (int id);
void sizeMenu (int id);
void mainMenu (int id);
void mouseFunc (int button, int state, int x, int y);
void reshape (GLsizei w, GLsizei h);

int pointsChosen, x1, y1, numberOfLists=0;
GLsizei ysize;

using namespace std;

int main (int argc, char** argv)
{
    int color_menu, size_menu;

    glutInit (&argc, argv);
    glutInitWindowSize (SIZE, SIZE);
    glutInitWindowPosition (100, 100);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow ("Menu Demonstration");

    glutDisplayFunc (display);
    glutMouseFunc (mouseFunc);
    glutReshapeFunc (reshape);

    color_menu = glutCreateMenu (colorMenu);
       glutAddMenuEntry ("Red", 1);
       glutAddMenuEntry ("Green", 2);
       glutAddMenuEntry ("Blue", 3);
       glutAddMenuEntry ("Black", 4);
    size_menu = glutCreateMenu (sizeMenu);
       glutAddMenuEntry ("1", 1);
       glutAddMenuEntry ("2", 2);
       glutAddMenuEntry ("3", 3);
    glutCreateMenu (mainMenu);
       glutAddSubMenu ("Color", color_menu);
       glutAddSubMenu ("Size", size_menu);
       glutAddMenuEntry ("Reset defaults", 1);
       glutAddMenuEntry ("Clear window", 2);
       glutAddMenuEntry ("Exit", 3);
    glutAttachMenu (GLUT_RIGHT_BUTTON);

    gfxinit ();
    glutMainLoop ();
    return 0;
}

void gfxinit (){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (0.0, SIZE - 1, 0.0, SIZE - 1);
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
       glColor3d (0.0, 0.0, 0.0);          
       glLineWidth (1.0);                  
    glEndList ();
    pointsChosen = 0;
    ysize = SIZE - 1;
}


void display (void)
{
    int i;

    glClear (GL_COLOR_BUFFER_BIT);
    for (i=1; i<=numberOfLists; i++) glCallList (i);
	glFlush ();
}

void mainMenu (int id)
{
    double lineWidth, color[4];

    switch (id)
    {
    case 1 : 
        glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
           glColor3d (0.0, 0.0, 0.0);
           glLineWidth (1.0);
        glEndList ();
        break;
    case 2 :
        glDeleteLists (1, numberOfLists);
        numberOfLists = 0;
        glGetDoublev (GL_LINE_WIDTH, &lineWidth);
        glGetDoublev (GL_CURRENT_COLOR, color);
        glNewList (++numberOfLists, GL_COMPILE);
           glColor4dv (color);
           glLineWidth (lineWidth);
        glEndList ();
        glutPostRedisplay ();
        break;
    case 3 :
        exit (0);
        break;
    default : 
        break;
    }
}

void colorMenu (int id)
{
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
    case 1 : 
        glColor3d (1.0, 0.0, 0.0);
        break;
    case 2 : 
        glColor3d (0.0, 1.0, 0.0);
        break;
    case 3 : 
        glColor3d (0.0, 0.0, 1.0);
        break;
    case 4 : 
        glColor3d (0.0, 0.0, 0.0);
        break;
    default : 
        break;
    }
    glEndList ();
    pointsChosen = 0;
}

void sizeMenu (int id)
{
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
    case 1 :
        glLineWidth (1.0);
        break;
    case 2 : 
        glLineWidth (2.0);
        break;
    case 3 : 
        glLineWidth (3.0);
        break;
    default : 
        break;
    }
    glEndList ();
}

void mouseFunc (int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        if (pointsChosen == 0)
        {
            x1 = x;
            y1 = ysize - y;
            pointsChosen = 1;
        }
        else
        {
            glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
               glBegin (GL_LINES);
                  glVertex2i (x1, y1);
                  glVertex2i (x, ysize-y);
               glEnd ();
            glEndList ();
			glFlush ();
            pointsChosen = 0;
        }
}

void reshape (GLsizei w, GLsizei h)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (0.0, w - 1, 0.0, h - 1);
    ysize = h - 1;

    glViewport (0, 0, w, h);
}