#include "Application.h"
#include "ModuleWindow.h"
#include "SDL\include\SDL.h"
#include "Globals.h"

ModuleWindow::ModuleWindow(){

}

ModuleWindow::~ModuleWindow(){

}

bool ModuleWindow::Init(){
	LOG("Init window");
	bool ret = true;
	if (SDL_Init(SDL_INIT_VIDEO) == 0){
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;
		int width = SCREEN_WIDTH*SCREEN_SIZE;
		int height = SCREEN_HEIGHT*SCREEN_SIZE;

		if (FULLSCREEN){
			flags |= SDL_WINDOW_FULLSCREEN;  //|= adds it as it's a set of bits
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		if (window != nullptr){
			surface = SDL_GetWindowSurface(window);
		}
		else{
			LOG("Window couldn't be created SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
	}
	else{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	return ret;
}

bool ModuleWindow::CleanUp(){
	LOG("Destroying SDL window and quitting all SDL systems");

	if (window != nullptr){
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}