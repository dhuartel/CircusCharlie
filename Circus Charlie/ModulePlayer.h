#pragma once

#include "Module.h"
#include "Point.h"

enum playerStatus{
	PLAYERSTANDING,
	PLAYERMOVINGONWARDS,
	PLAYERMOVINGBACKWARDS,
	PLAYERJUMPING,
	PLAYERVICTORY
};

class ModulePlayer :public Module{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();

private:
	playerStatus status;
	//bool victory;

	fPoint position;
	float movementSpeed=1;

	int jumpCommited = 0;
};