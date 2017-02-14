#pragma once

#include "Globals.h"
class Animation;

class Graphics{
public:
	Graphics();
	void LoadGraphics();
	void UnloadGraphics();
public:
	SDL_Texture* sprites;
	Animation bigRingOfFire;
	Animation smallRingOfFire;
};