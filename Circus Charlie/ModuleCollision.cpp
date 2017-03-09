#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"

ModuleCollision::ModuleCollision(){
	//Setting possible collisions matrix
	possibleCollisions[PLAYER][PLAYER] = false;
	possibleCollisions[PLAYER][HARM] = true;

	possibleCollisions[HARM][PLAYER] = true;
	possibleCollisions[HARM][HARM] = false;
}

ModuleCollision::~ModuleCollision(){
}

update_status ModuleCollision::PreUpdate(){
	//Release flagged colliders
	list<Collider*>::iterator it = setOfColliders.begin();
	while (it != setOfColliders.end()){
		if ((*it)->flagErase){
			RELEASE(*it);
			it = setOfColliders.erase(it);
		}
		else{
			++it;
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update(){
	list<Collider*>::iterator it;
	list<Collider*>::iterator it2;
	for (it = setOfColliders.begin(); it != setOfColliders.end(); ++it){
		it2 = it;
		++it2;
		for (it2; it2 != setOfColliders.end(); ++it2){
			if (DetectCollision((*it)->collisionBox, (*it2)->collisionBox)){
				if (possibleCollisions[(*it)->type][(*it2)->type]){
					(*it)->mod->OnCollision(*it, *it2);
					(*it2)->mod->OnCollision(*it, *it2);
				}
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleCollision::PostUpdate(){
	if (App->debugMode){
		list<Collider*>::iterator it;
		for (it = setOfColliders.begin(); it != setOfColliders.end(); ++it){
			switch ((*it)->type){
			case PLAYER:
				App->renderer->DrawRect((*it)->collisionBox, 0, 0, 255, TRANSPARENTALPHA);
				break;
			case HARM:
				App->renderer->DrawRect((*it)->collisionBox, 255, 0, 0, TRANSPARENTALPHA);
				break;
			}
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleCollision::CleanUp(){
	list<Collider*>::reverse_iterator it;
	for (it = setOfColliders.rbegin(); it != setOfColliders.rend(); ++it){
		RELEASE(*it);
	}
	setOfColliders.clear();
	return true;
}

Collider* ModuleCollision::CreateCollider(SDL_Rect rect, Module* mod, colliderType col){
	Collider* collider = new Collider(rect, mod, col);
	setOfColliders.push_back(collider);
	return collider;
}

bool ModuleCollision::DetectCollision(SDL_Rect a, SDL_Rect b){
	return SDL_HasIntersection(&a, &b);
}