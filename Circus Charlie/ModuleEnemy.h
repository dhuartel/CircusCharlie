#pragma once

#include "Module.h"

class ModuleEnemy : public Module{
public:
	ModuleEnemy(bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void Moving(bool onwards, float speed);
private:
	int baseDistanceSmall = 235;
	int baseDistanceBig = 325;
	int distanceVariation = 90;
	int currentDistance;
	float ringOfFirePos = 636;
	int ringCountToSmall = 5;
	bool bigDistanceBool = true;
	int fireJarDistance = 26;

	float ringOfFireSpeed = 0.8f;

	Collider* fireJarCollider1;
	Collider* fireJarCollider2;
	Collider* ringOfFireCollider1;
	Collider* ringOfFireCollider2;
	void FireJarDrawer();
};