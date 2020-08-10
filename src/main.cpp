#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <stdlib.h>

#include <iostream>

using namespace::std;

int Display::GetInstance();
int Display::Execute(int argc, char *argv[]);

int main (int argc, char *argv[]) {
	
	Display::GetInstance()->Execute(argc, argv);

	while(1);

	return EXIT_SUCCESS;
}
