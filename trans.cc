#include<iostream>
#include<GL/glut.h>
using namespace std

void openGL_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
                    zoom += 1;
            else
                    zoom -= 1f;

            Invalidate();
            glDraw();
        }

        void openGL_MouseMove(object sender, MouseEventArgs e)
        {
            if (MouseD == 2)
            {
                yrot -= (mouX - e.Location.X)/5;
                if ((yrot > 360) || (yrot < -360)) yrot = 0;
                xrot -= (mouY - e.Location.Y)/5;
                if ((xrot > 360) || (xrot < -360)) xrot = 0;
            }

            if (MouseD == 1)
            {
                xpos -= (mouX - e.Location.X) / 100;
                ypos += (mouY - e.Location.Y) / 100;
            }

            if ((MouseD == 1) | (MouseD == 2))
            {
                Invalidate();
                glDraw();
            }

            mouX = e.Location.X;
            mouY = e.Location.Y;

        }

        void openGL_MouseUp(object sender, MouseEventArgs e)
        {
            BodGL bod;

            if ((AtrBod == true) & (MouseD == 0))
            {
                pocetAtrBodov++;
                
                bod = new BodGL();
                bod.Quad = GLU.gluNewQuadric();
                bod.bod = new Bod();
                bod.bod.Pozicia = openGLPos(e.Location.X, e.Location.Y);
                bod.bod.Typ = 1;
                bod.bod.Farba = new Vektor(0.5, 0.5, 0.5);
                
                poleBodov.Add(bod);

                Invalidate();
                glDraw();
            }

            MouseD = 0;

        }

        void openGL_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
                MouseD = 2;
            else
                if (AtrBod) MouseD = 0; else MouseD = 1;
        }

        void openGL_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.A) AtrBod = true;
        }

        void openGL_KeyUp(object sender, KeyEventArgs e)
        {
            AtrBod = false;
        }

Vektor openGLPos(int x, int y)
        {
            int[] viewport = new int[4];
            double[] modelview = new double[16];
            double[] projection = new double[16];
            double outX, outY, outZ;

            GL.glGetDoublev( GL.GL_MODELVIEW_MATRIX, modelview );
            GL.glGetDoublev( GL.GL_PROJECTION_MATRIX, projection );
            GL.glGetIntegerv( GL.GL_VIEWPORT, viewport );

            Vektor win = new Vektor((float)x, (float)viewport[3] - y, 0f);

            unsafe
            {
                GL.glReadPixels(x, (int)win.Y, 1, 1, GL.GL_DEPTH_COMPONENT, GL.GL_FLOAT, (&outZ));
            }

            GL.gluUnProject((float)win.X, (float)win.Y, (float)win.Z, modelview, projection, viewport, out outX, out outY, out outZ);

            Vektor temp = new Vektor(outX, outY, outZ - 10);
           
            return temp;
        }

void glDraw()
    {

            GL.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);    
            
            GL.glPushMatrix();
            GL.glLoadIdentity();

            GL.glTranslatef(xpos, ypos, zoom);
            GL.glRotatef(xrot, 1.0f, 0.0f, 0.0f);
            GL.glRotatef(yrot, 0.0f, 1.0f, 0.0f);
            

            if (pocetAtrBodov > 0)
            {
                foreach (BodGL B in poleBodov)
                {
                    VykresliAtrBod(B.Quad, B.bod.Priemer, B.bod.Farba);
                }
            }

            GL.glPopMatrix();
    }


        void VykresliAtrBod(GLUquadric Q, double r , Vektor farba)
        {
            unsafe
            {
                GL.glColor3f((float)farba.X, (float)farba.Y, (float)farba.Z);

                GL.gluQuadricDrawStyle(Q, GL.GLU_SILHOUETTE); /* smooth shaded */
                GL.gluQuadricNormals(Q, GL.GLU_SMOOTH);

                
                GL.gluSphere(Q, r, 10, 10);

            }
        }
