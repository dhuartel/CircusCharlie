#include "ModuleEnemy.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Graphics.h"
#include "ModuleLevels.h"
#include "ModuleCollision.h"
#include <time.h>

ModuleEnemy::ModuleEnemy(bool start_enabled):Module(start_enabled){

}

ModuleEnemy::~ModuleEnemy(){

}

bool ModuleEnemy::Start(){
	srand(time(NULL));
	currentDistance = baseDistanceSmall + (rand() % distanceVariation);
	fireJarDistance = 26 + App->graphics->fireJar.GetFrame(0).w;

	SDL_Rect aux;
	aux.h = 0;
	aux.w = 0;
	aux.x = 0;
	aux.y = 0;
	fireJarCollider1 = App->collision->CreateCollider(aux, this, HARM);
	fireJarCollider2 = App->collision->CreateCollider(aux, this, HARM);
	ringOfFireCollider1 = App->collision->CreateCollider(aux, this, HARM);
	ringOfFireCollider2 = App->collision->CreateCollider(aux, this, HARM);
	return true;
}

update_status ModuleEnemy::PreUpdate(){
	//The ring always moves, the rest depend on the player movement
	ringOfFirePos -= ringOfFireSpeed;
	if (ringOfFirePos <= 0){
		ringOfFirePos += currentDistance;
		--ringCountToSmall;
		if (ringCountToSmall == 1 || ringCountToSmall == 0){
			currentDistance = 408;
		}
		else{
			if (ringCountToSmall < 0){
				ringCountToSmall += 16;
			}
			if (bigDistanceBool){
				bigDistanceBool = false;
				currentDistance = baseDistanceBig + (rand() % distanceVariation);
			}
			else{
				bigDistanceBool = true;
				currentDistance = baseDistanceSmall + (rand() % distanceVariation);
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemy::Update(){
	if (ringCountToSmall == 1){
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos, 188, &App->graphics->bigRingOfFireBack.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + currentDistance, 188, &App->graphics->smallRingOfFireBack.GetCurrentFrame());
	}
	else if (ringCountToSmall == 0){
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos, 188, &App->graphics->smallRingOfFireBack.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + currentDistance, 188, &App->graphics->bigRingOfFireBack.GetCurrentFrame());
	}
	else{
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos, 188, &App->graphics->bigRingOfFireBack.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + currentDistance, 188, &App->graphics->bigRingOfFireBack.GetCurrentFrame());
	}
	ringOfFireCollider1->collisionBox.x = ringOfFirePos+12;
	ringOfFireCollider1->collisionBox.y = 188 + App->graphics->bigRingOfFireBack.GetFrame(0).h-20;
	ringOfFireCollider1->collisionBox.w = 24;
	ringOfFireCollider1->collisionBox.h = 20;
	FireJarDrawer();
	return UPDATE_CONTINUE;
}

update_status ModuleEnemy::PostUpdate(){
	//The +26 should be +RingOfFireFront.GetCurrentFrame().w/2
	if (ringCountToSmall == 1){
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + 26, 188, &App->graphics->bigRingOfFireFront.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + currentDistance + 25, 188, &App->graphics->smallRingOfFireFront.GetCurrentFrame());
	}
	else if (ringCountToSmall == 0){
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + 25, 188, &App->graphics->smallRingOfFireFront.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + currentDistance + 26, 188, &App->graphics->bigRingOfFireFront.GetCurrentFrame());
	}
	else{
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + 26, 188, &App->graphics->bigRingOfFireFront.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, ringOfFirePos + currentDistance + 26, 188, &App->graphics->bigRingOfFireFront.GetCurrentFrame());
	}
	return UPDATE_CONTINUE;
}

bool ModuleEnemy::CleanUp(){
	return true;
}

void ModuleEnemy::Moving(bool onwards,float speed){
	if (onwards){
		ringOfFirePos -= speed;
		if (ringOfFirePos <= 0){
			ringOfFirePos += currentDistance;
			--ringCountToSmall;
			if (ringCountToSmall == 1 || ringCountToSmall == 0){
				currentDistance = 408;
			}
			else{
				if (ringCountToSmall < 0){
					ringCountToSmall += 16;
				}
				if (bigDistanceBool){
					bigDistanceBool = false;
					currentDistance = baseDistanceBig + (rand() % distanceVariation);
				}
				else{
					bigDistanceBool = true;
					currentDistance = baseDistanceSmall + (rand() % distanceVariation);
				}
			}
		}
	}
	else{
		ringOfFirePos += speed;
	}
}

void ModuleEnemy::FireJarDrawer(){
	SDL_Rect currentFrame = App->graphics->fireJar.GetCurrentFrame();
	int meterCounterPos = App->levels->meterCounterPos;
	App->renderer->Blit(App->graphics->sprites, meterCounterPos - fireJarDistance, 426 - currentFrame.h, &currentFrame);
	App->renderer->Blit(App->graphics->sprites, meterCounterPos + SCREEN_WIDTH - fireJarDistance, 426 - currentFrame.h, &currentFrame);
}