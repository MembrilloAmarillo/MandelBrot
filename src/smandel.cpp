#include <GLUT/glut.h>
#include <complex>
#include <iostream>

#include "scomplex.h"

#define WIDTH   1440
#define HEIGHT  1440

#define N       255 //Max RGB value

#define MAX_ITER    300

void initGL () {
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
}

void get_rgb (int n, int *r, int *g, int *b) {
    double t = (double)n / (double)MAX_ITER;

    *r = (int)(9*(1-t)*t*t*t*N);
	*g = (int)(15*(1-t)*(1-t)*t*t*N);
	*b = (int)(8.5*(1-t)*(1-t)*(1-t)*t*N);	
}

void mandel ( int x, int y, int r, int g, int b ) {
    std::complex<double> point((double)x/WIDTH-1.5, (double)y/HEIGHT-0.5);

    std::complex<double> z(0,0);
    unsigned int nb_iter = 0;
    while (abs(z) < 2 && nb_iter <= MAX_ITER) {
        z = z * z + point;
        /* Solo para motivos de depuracion */
        // std::cout << "Z value: " << z << std::endl;
        nb_iter++;
    }
    if (nb_iter < MAX_ITER) {
        get_rgb( (N*nb_iter) / MAX_ITER , &r, &g, &b );
    }else {
        get_rgb( nb_iter, &r, &g, &b );
    }
    
    glColor3f( r, g, b );
    glVertex2i( x, y );
}

void display () {
    
    int r, g, b;
    r = g = b = 0;
    /* clear the color buffer */
    glClear( GL_COLOR_BUFFER_BIT );
    glOrtho( 0, WIDTH, 0, HEIGHT, -1, 1 );
    /* operate on Model-View matrix */
    glMatrixMode( GL_MODELVIEW );
    /* use the identity model-view matrix */
    glLoadIdentity();

    glBegin( GL_POINTS ); 
    for( int i = 0; i < WIDTH; i++ ) {
        for ( int j = 0; j < HEIGHT; j++ ) {
            mandel(i, j, r, g, b);
        }
    }
    glEnd();
    //glFlush();
    glutSwapBuffers();
}

void reshape (GLsizei width, GLsizei height) {
    /* note that we accept GLsizei non-negative parameters */

   /* Compute aspect ratio of the new window and prevent
    * a possible divide by zero with an assumption. */
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   /* Set the viewport to cover the new window */
   glViewport(0, 0, width, height);
 
   /* Set the aspect ratio of the clipping area to match the viewport */
   glMatrixMode(GL_PROJECTION);  /* operate on the Projection matrix */
   glLoadIdentity();
   if (width >= height) {
     /* aspect >= 1, set the height from -1 to 1, with larger width */
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      /* aspect < 1, set the width to -1 to 1, with larger height */
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}

int main (int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("MandelBrot");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutMainLoop();
    return 0;
}
