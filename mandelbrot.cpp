#include "mandelbrot.h"

double scalate( double X, double low, double high, int size )
{
    if ( low < 0  ) low  *= -1;
    if ( high < 0 ) high *= -1;
    double scalated = ((X * high) / size ) - low + (X / (size / low));

    return scalated;
}

unsigned int mandelbrot( Complex c, int max_iter ) 
{
	double x   = 0;
	double y   = 0;

	double xtemp   = 0;
	double ytemp   = 0;

	unsigned int iteration = 0;

	while ( ( x + y ) <= 4 && iteration <= max_iter ) {
        ytemp = (xtemp + xtemp) * ytemp + c.getImaginary();
        xtemp = x - y + c.getReal();
        x = xtemp * xtemp;
        y = ytemp * ytemp;
		++iteration;
	}
	return iteration;
}

