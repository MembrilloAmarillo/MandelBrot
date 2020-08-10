#ifndef __NSLOG_H__
	#define __NSLOG_H__

	#include <stdio.h>

	#define DEBUG 1

	#ifdef DEBUG
	    #define NSLog(...) printf(__VA_ARGS__); printf("\n");
	#else
	    #define NSLog(...) ;
	#endif

#endif
