#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "structs.h"

#define msg "Esto es una prueba\n"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

Display* show_display( Window *w, int* s);

void linear ( long double*, long double*, long double*, long double* );

int main (int argc, char *argv[]) {
  
  Display *dsp = NULL;
  Window w;
  XEvent e;
  int s;
  dsp = show_display(&w, &s);
  
  struct parameters* p = NULL;

  if (dsp == NULL) {
	fprintf(stderr, "ERROR: pointer to dsp failed\n");
	exit(0);
  }

  pthread_t thread;
 // pthread_create(&thread, NULL, linear, p);
  
  while(1) {
	XNextEvent(dsp, &e);
	if (e.type == Expose) {
	 XFillRectangle(dsp, w, DefaultGC(dsp, s), 20, 20, 10, 10);
	 XDrawString(dsp, w, DefaultGC(dsp, s), 10, 50, msg, strlen(msg));
	}
	if (e.type == KeyPress)
	  break;
  }

  XCloseDisplay(dsp);

  return ( EXIT_SUCCESS );
}
