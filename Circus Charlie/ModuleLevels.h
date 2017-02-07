#pragma once

#include "Module.h"

struct SDL_Texture;

class ModuleLevels : public Module{
public:
	ModuleLevels(bool start_enabled = true);
	~ModuleLevels();

	bool Start();
	update_status Update();
	update_status PostUpdate();//For lives and point hud
	bool CleanUp();

private:
	SDL_Texture* lowerBackgroundGraphics = nullptr;//I don't add this to a graphics class apart yet, will be decided later
	SDL_Texture* upperBackgroundGraphics = nullptr;//I don't add this to a graphics class apart yet, will be decided later
	SDL_Texture* hudGraphics = nullptr;//I don't add this to a graphics class apart yet, will be decided later
	SDL_Rect lowerBackground;
	SDL_Rect upperBackground;
	SDL_Rect hud;
};