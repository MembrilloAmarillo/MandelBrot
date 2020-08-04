#include <complex.h>
#include <math.h>

#include "structs.h"


//Xn+1 = R*Xn(1 - Xn)    R belongs to [1,4]
//Z = R(1/2 - X), C = R/2*(1 - R/2)

long double intersection_x ( struct parameters *param ) {
  param->next->x = param->r * param->x*(1 - param->x);
  
  return param->next->x;
}

long double correspondence_c ( struct parameters *param ) {
  param->c = (param->r/2) * (1 - param->r);
  
  return param->c;
}

long double correspondence_z ( struct parameters *param ) {
  param->z = param->r*(1/2 - param->x);

  return param->z;
}

void non_set ( struct parameters *param) {
  if ((param->z * param->z) >= 4) {
	param->belong = 0;
  }else
	param->belong = 1;
}


