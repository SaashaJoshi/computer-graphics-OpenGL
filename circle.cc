
void my_display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0); 
    int i; 
    float Pi = 3.14159f;
    float radius = 0.08f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(my_x, my_y);
    for(i = 0; i <= 360; i++) {
        glVertex2f(my_x +radius * cos(i * Pi/180),
                   my_y +radius * sin(i * Pi/180));
    }
    glEnd();
    glutSwapBuffers(); // swaps buffers
    return;
}

void my_mouse(int b, int s, int x, int y) {
    switch (b) {            /* b indicates the button */
        case GLUT_LEFT_BUTTON:
            if (s == GLUT_DOWN)  {  /* button pressed */
                my_x = x;
                my_y = window_h - y;
                my_display();
            }
            break;
    }
}


/*
GLint viewport[4];
glPushAttrib(GL_TRANSFORM_BIT);
glGetIntegerv(GL_VIEWPORT, viewport);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
glPopAttrib();
glDisable(GL_DEPTH_TEST);
glPushMatrix();
glLoadIdentity();

glPopMatrix();
glPushAttrib(GL_TRANSFORM_BIT);
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glPopAttrib();
glEnable(GL_DEPTH_TEST);
*/