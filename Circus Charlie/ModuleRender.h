#pragma once
#include "Module.h"

struct SDL_Renderer;

class ModuleRender: public Module{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, int alpha = 255);
	void DrawRect(SDL_Rect rect, int r, int g, int b, int alpha);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
};