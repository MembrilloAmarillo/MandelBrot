#ifndef _MANDELBROT_H_
#define _MANDELBROT_H_

#include <stdint.h>

#include "scomplex.h"

unsigned int mandelbrot( Complex, int );
double scalate( double, double, double, int ); 
uint32_t colorize( uint8_t );

#endif 
