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

	void MovingPlayer(bool onwards, float speed);

private:
	bool victory = false;

	int baseDistanceSmall=235;
	int baseDistanceBig = 325;
	int distanceVariation = 90;
	int currentDistance;
	float ringOfFirePos = 636;
	int ringCountToSmall = 5;
	bool bigDistanceBool = true;
	int meterCounterPos = 22;
	int metersLeft = 10;//multiplied by 10
	int fireJarDistance = 26;

	float ringOfFireSpeed = 0.8f;

	int elephantPos = 201;
	SDL_Texture* backgroundGraphics = nullptr;//I don't add this to a graphics class apart yet, will be decided later
	SDL_Rect lowerBackground;
	SDL_Rect elephantUpperBackground;
	Animation upperBackground;
	SDL_Rect hud;

	void MeterDrawer();
	void FireJarDrawer();
};