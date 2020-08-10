#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <stdlib.h>

#include <iostream>

#include "display.h"

using namespace std;

int initialize ( int argc, char *argv[] );

int main ( int argc, char *argv[] ) {
	
	initialize(argc, argv);
	
	return EXIT_SUCCESS;
}

int initialize ( int argc, char *argv[] ) {
	return Display::GetInstance()->Execute( argc, argv );	
}
