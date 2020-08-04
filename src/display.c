#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"

#define DSP_ERROR "Error: Cannot open display\n"

Display* show_display ( Window *w, int *s ) {
  
  Display* disp_name;

  disp_name = XOpenDisplay(NULL);
  if ( disp_name == NULL ) {
	fprintf(stderr, DSP_ERROR);
	exit(1);
  }
  
  *s = DefaultScreen(disp_name);
  *w = XCreateSimpleWindow(disp_name, RootWindow(disp_name, *s),50, 50, 300, 300, 1,
	  BlackPixel(disp_name, *s), WhitePixel(disp_name, *s));
  
  XSelectInput(disp_name, *w, ExposureMask | KeyPressMask);
  XMapWindow(disp_name, *w);

  return disp_name;

}
