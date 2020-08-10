#pragma once

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <SDL2/Sdl.h>

class Display {
	
	private:
		
		static Display Instance;
		
		/* Solo compila bajo std=C++11 */
		bool Running = true;

		SDL_Window *Window = NULL;
		SDL_Renderer *Renderer = NULL;
		SDL_Surface *PrimarySurface = NULL;

		static const int WindowWidth = 1024;
		static const int WindowHeight = 768;
	
		Display();

		/* Capturar los eventos */
		void OnEvent(SDL_Event *Event);

		/* Iniciamos el display */
		bool Init();

		void Loop();

		/* Renderizamos el loop */
		void Render();

		/* Limpieza de recursos */
		void Cleanup();

	public:
		int Execute(int argc, char *argv[]);
		
		SDL_Renderer *GetRenderer();

		static Display *GetInstance();

		static int GetWindowWidth();
		static int GetWindowHeight();
};

#endif
