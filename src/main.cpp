#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <stdlib.h>

#include <iostream>

using namespace::std;

Display::Display Instance;

int Display::Execute(int argc, char *argv[]);

int main (int argc, char *argv[]) {
	
	Display::Execute(argc, argv);

	while(1);

	return EXIT_SUCCESS;
}
