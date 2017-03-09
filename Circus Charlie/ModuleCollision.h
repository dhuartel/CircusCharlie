#pragma once

#include "Module.h"
#include <list>
#include "Collider.h";

class ModuleCollision :public Module{
public:
	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	//It returns the created collider to be stored in the class that creates it as well, so it can change position
	Collider* CreateCollider(SDL_Rect, Module*, colliderType);

private:
	list<Collider*> setOfColliders;
	bool DetectCollision(SDL_Rect, SDL_Rect);
	//Right now this matrix isn't necesary, but will be if the num of types grow
	bool possibleCollisions[NUMOFCOLLISIONTYPES][NUMOFCOLLISIONTYPES];
};