#pragma once

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module{
public:
	ModuleWindow();
	~ModuleWindow();

	bool Init();
	bool CleanUp();

public:
	//The window we'll render into
	SDL_Window* window = nullptr;

	//Surface contained by the window
	SDL_Surface* surface = nullptr;
};