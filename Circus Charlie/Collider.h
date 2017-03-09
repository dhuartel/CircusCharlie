#pragma once

#include "Globals.h"

class Module;

enum colliderType{
	PLAYER=0,
	HARM,

	NUMOFCOLLISIONTYPES
};

enum colliderStatus{
	OUT=0,
	IN
};

class Collider{
public:
	Collider(SDL_Rect, Module*, colliderType);
	~Collider();
	void flagRelease();
public:
	SDL_Rect collisionBox;
	Module* mod = nullptr;
	bool flagErase;
	colliderType type;
	colliderStatus status;
};