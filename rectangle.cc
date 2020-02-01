#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define PI 3.1415926
using namespace std;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // center rectangle
    glBegin(GL_POLYGON);
    glVertex3f(100, 40, 0.0);
    glVertex3f(300, 40, 0.0);
    glVertex3f(300, 120, 0.0);
    glVertex3f(100, 120, 0.0);
    glEnd();
    // right rectangle
    glBegin(GL_POLYGON);
    glVertex3f(320, 40, 0.0);
    glVertex3f(300, 40, 0.0);
    glVertex3f(300, 120, 0.0);
    glVertex3f(320, 120, 0.0);
    glEnd();
    //left rectangle
    glBegin(GL_POLYGON);
    glVertex3f(100, 40, 0.0);
    glVertex3f(80, 40, 0.0);
    glVertex3f(80, 120, 0.0);
    glVertex3f(100, 120, 0.0);
    glEnd();
    //upper rectangle
    glBegin(GL_POLYGON);
    glVertex3f(100, 140, 0.0);
    glVertex3f(300, 140, 0.0);
    glVertex3f(300, 120, 0.0);
    glVertex3f(100, 120, 0.0);
    glEnd();
    //lower rectangle
    glBegin(GL_POLYGON);
    glVertex3f(100, 40, 0.0);
    glVertex3f(300, 40, 0.0);
    glVertex3f(300, 20, 0.0);
    glVertex3f(100, 20, 0.0);
    glEnd();

    const unsigned int triangles = 20; // number of triangles
    const float twoPi = 2.0f * 3.14159f;
    glBegin(GL_TRIANGLE_FAN);
    // origin
    float delta = twoPi / triangles;
    for (unsigned int i = 0; i <= triangles; i++)
        glVertex2f(100 + (20 * cos(i * delta)),
                   120 + (20 * sin(i * delta)));
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    // origin
    delta = twoPi / triangles;
    for (unsigned int i = 0; i <= triangles; i++)
        glVertex2f(100 + (20 * cos(i * delta)),
                   40 + (20 * sin(i * delta)));
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    // origin
    delta = twoPi / triangles;
    for (unsigned int i = 0; i <= triangles; i++)
        glVertex2f(300 + (20 * cos(i * delta)),
                   120 + (20 * sin(i * delta)));
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    // origin
    delta = twoPi / triangles;
    for (unsigned int i = 0; i <= triangles; i++)
        glVertex2f(300 + (20 * cos(i * delta)),
                   40 + (20 * sin(i * delta)));
    glEnd();
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 150);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}