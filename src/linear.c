#include <math.h>
#include <limits.h>
#include <stdio.h>

#include "structs.h"

long double intersection_x ( struct parameters* );
long double correspondence_c ( struct parameters* );
long double correspondence_z ( struct parameters* );
void non_set ( struct parameters* );
 
struct parameters p = {
  .z = 1/3,
  .c = -1,
  .r = 1/4, 
  .x = 0,
  .belong = 1
};

void linear ( long double *x, long double *z, 
	long double *c, long double *r ) 
{
  *x = intersection_x ( &p );
  *z = correspondence_z ( &p );
  *c = correspondence_c ( &p );
	
  printf("x value : %LF\n", *x);
  printf("z value : %LF\n", *z);
  printf("c value : %LF\n", *c);
  non_set ( &p );

}
