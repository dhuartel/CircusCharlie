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
	SDL_Texture* misc;
	Animation bigRingOfFire;
	Animation smallRingOfFire;
	SDL_Rect meterCounter;
	Animation movingLionBackwards;
	Animation movingLionOnwards;
	Animation movingPlayerOnLion;
	SDL_Rect deadLion;
	SDL_Rect deadPlayerOnLion;
};