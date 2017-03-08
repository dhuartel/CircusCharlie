#pragma once

#include "Globals.h"

enum audioEffects{
	START=0,
	JUMP,
	DIE,
	COIN,
	CATCH,
	PAUSE
};

class AudioEffects{
public:
	AudioEffects();
	void LoadFxs();
	void PlayFX(audioEffects id);
private:
	unsigned int startFx = 0;
	unsigned int jumpFx = 0;
	unsigned int dieFx = 0;
	unsigned int coinFx = 0;
	unsigned int catchFx = 0;
	unsigned int pauseFx = 0;
};