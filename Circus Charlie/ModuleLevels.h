#pragma once

#include "Module.h"

struct SDL_Texture;

class ModuleLevels : public Module{
public:
	ModuleLevels(bool start_enabled = true);
	~ModuleLevels();

	bool Start();
	update_status PreUpdate();//For moving background
	update_status Update();
	update_status PostUpdate();//For lives and point hud
	bool CleanUp();

private:
	bool victory = false;

	int baseDistanceSmall=235;
	int baseDistanceBig = 325;
	int distanceVariation = 90;
	int currentDistance;
	float ringOfFirePos = 636;
	int ringCountToSmall = 6;
	bool bigDistanceBool = true;
	int meterCounterPos = 22;

	int elephantPos = 201;
	SDL_Texture* backgroundGraphics = nullptr;//I don't add this to a graphics class apart yet, will be decided later
	SDL_Rect lowerBackground;
	SDL_Rect elephantUpperBackground;
	Animation upperBackground;
	SDL_Rect hud;
};