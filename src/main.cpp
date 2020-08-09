#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <stdlib.h>

#include <iostream>

using namespace::std;

int main (int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		cout << "Error creando ventana" << endl;
	SDL_Window* win = SDL_CreateWindow("MandelBrot",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			300,300,0);

	while(1);

	return EXIT_SUCCESS;
}
