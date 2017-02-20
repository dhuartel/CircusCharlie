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
	Animation bigRingOfFireBack;
	Animation bigRingOfFireFront;
	Animation smallRingOfFireBack;
	Animation smallRingOfFireFront;
	SDL_Rect meterCounter;
	Animation movingLionBackwards;
	Animation movingLionOnwards;
	Animation movingPlayerOnLion;
	SDL_Rect deadLion;
	SDL_Rect deadPlayerOnLion;
	Animation numbers;
};