#include "Module.h"
#include "Collider.h"

Collider::Collider(SDL_Rect box, Module* m, colliderType colType){
	collisionBox = box;
	mod = m;
	type = colType;
	flagErase = false;
	status = OUT;
}

Collider::~Collider(){
}

void Collider::flagRelease(){
	flagErase = true;
}