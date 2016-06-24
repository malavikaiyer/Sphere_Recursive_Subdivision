#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


float v[][3]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333}, {-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};

int n=4;


void triangle (float a[], float b[], float c[])
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void normal (float p[])
{
    float f= 0.0;
    int i;
    for(i=0; i<3; i++)
        f+=p[i]*p[i];
    f=sqrt(f);
    if(f>0.0)
        for(i=0; i<3; i++)
        p[i]/=f;
}

void divide_triangle (float a[], float b[], float c[], int m)
{
    float v1[3], v2[3], v3[3];
    int j;
    if(m>0)
    {
        for(j=0; j<3; j++)
            v1[j]=a[j]+b[j];
        normal(v1);
        for(j=0; j<3; j++)
            v2[j]=a[j]+c[j];
        normal(v2);
        for(j=0; j<3; j++)
            v3[j]=b[j]+c[j];
        normal(v3);
        divide_triangle  (a, v1, v2, m-1);
        divide_triangle (c, v2, v3, m-1);
        divide_triangle (b, v3, v1, m-1);
        divide_triangle (v1, v3, v2, m-1);
    }
    else
        triangle (a,b,c);
}

void tetrahedron (int m)
{
    divide_triangle (v[0], v[1], v[2], m);
    divide_triangle (v[3], v[2], v[1], m);
    divide_triangle (v[0], v[3], v[1], m);
    divide_triangle (v[0], v[2], v[3], m);
}

void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    tetrahedron(n);
    glutSwapBuffers ();
}

void myReshape (int w, int h)
{
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    if (w <= h)
        glOrtho(-1.95, 1.95, -1.95 * (GLfloat) h / (GLfloat) w,
                1.95 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-1.95 * (GLfloat) w / (GLfloat) h,
                1.95 * (GLfloat) w / (GLfloat) h, -1.95, 1.95, -10.0, 10.0);
    glMatrixMode (GL_MODELVIEW);
    glutPostRedisplay ();
}

void myinit ()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f (0.0, 0.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Sphere");
    myinit ();
    glutReshapeFunc (myReshape);
    glutDisplayFunc (display);
    glutMainLoop ();
    return 0;
}