#include <SDL2/SDL.h>

#include "log.h"

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

Display Display::Instance;

Display::Display() {}

void Display::OnEvent(SDL_Event *Event) {}

bool Display::Init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		NSLog("Unable to Init SDL: %s", SDL_GetError());
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		NSLog("Unable to Init hinting: %s", SDL_GetError());
	}

	if((Window = SDL_CreateWindow(
		"My SDL Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)
	) == NULL) {
		NSLog("Unable to create SDL Window: %s", SDL_GetError());
		return false;
	}

	PrimarySurface = SDL_GetWindowSurface(Window);

	if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
	    NSLog("Unable to create renderer");
	    return false;
	}

	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

	return true;
}

void Display::Loop() {}

void Display::Render() {
	SDL_RenderClear(Renderer);
	
	SDL_RenderPresent(Renderer);
}

void Display::Cleanup() {

	if(Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if(Window) {
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

	SDL_Quit();
}

int Display::Execute(int argc, char* argv[]) {
	
	if(!Init()) return 0;

	SDL_Event Event;

	while(Running) {
		while(SDL_PollEvent(&Event) != 0) {
			OnEvent(&Event);

			if(Event.type == SDL_QUIT) Running = false;
		}

		Loop();
		Render();

		SDL_Delay(1); // Breath
	}

	Cleanup();

	return 1;
}

SDL_Renderer* Display::GetRenderer() { return Renderer; }


Display* Display::GetInstance() { return &Display::Instance; }

int Display::GetWindowWidth()  { return WindowWidth; }
int Display::GetWindowHeight() { return WindowHeight; }


