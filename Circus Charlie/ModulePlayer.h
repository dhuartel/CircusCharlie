#pragma once

#include "Module.h"
#include "Point.h"

enum playerStatus{
	PLAYERSTANDING,
	PLAYERMOVINGONWARDS,
	PLAYERMOVINGBACKWARDS,
	PLAYERJUMPING,
	PLAYERDEAD,
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

	Collider* myCollider;
	//bool victory;

	float startHeight;
	fPoint position;
	float movementSpeed=2;
	float jumpSpeed = 6;
	float jumpAceleration=-12.0f/119.0f;

	float jumpCommited = 0;
};