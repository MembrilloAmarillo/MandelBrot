
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct parameters {
  long double z;
  long double r;
  long double c;
  long double x;
  unsigned int belong : 1;
  struct parameters *next;
};

enum {
  blue,
  red,
  green,
  black,
  white
};

#endif
