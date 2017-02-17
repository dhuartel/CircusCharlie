#include "Application.h"
#include "ModuleLevels.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "Graphics.h"
#include <time.h>

ModuleLevels::ModuleLevels(bool start_enabled) : Module(start_enabled){
	lowerBackground.x = 0;
	lowerBackground.y = 318;
	lowerBackground.w = 636;
	lowerBackground.h = 279;

	//84
	elephantUpperBackground.x = 0;
	elephantUpperBackground.y = 78;
	elephantUpperBackground.w = 84;
	elephantUpperBackground.h = 120;

	upperBackground.frames.push_back({ 84, 78, 552, 120 });
	upperBackground.frames.push_back({ 84, 198, 552, 120 });
	upperBackground.speed = 0.01f;
	upperBackground.loop = false;
	upperBackground.SetFrame(2);

	hud.x = 0;
	hud.y = 0;
	hud.w = 636;
	hud.h = 78;

	//636x477 597 289 188
}

ModuleLevels::~ModuleLevels(){}

//Load textures, set camera and enable other modules 
bool ModuleLevels::Start(){
	backgroundGraphics = App->textures->Load("background/backgroundFile.png");
	srand(time(NULL));
	currentDistance = baseDistanceSmall + (rand() % distanceVariation);

	return true;
}

//Unload textures
bool ModuleLevels::CleanUp(){
	LOG("Unloading levels scene");

	App->textures->Unload(backgroundGraphics);

	return true;
}

//PreUpdate: move background
update_status ModuleLevels::PreUpdate(){
	if (App->input->GetKey(SDL_SCANCODE_F)){
		upperBackground.loop = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT)){
		if (--elephantPos < 0 - elephantUpperBackground.w){
			elephantPos = SCREEN_WIDTH - elephantUpperBackground.w;
		}
		if (--meterCounterPos<-112){
			meterCounterPos += 461;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT)){
		if (++elephantPos > SCREEN_WIDTH){
			elephantPos = 0;
		}
		if (++meterCounterPos<-112){
			meterCounterPos += 461;
		}
	}
	if ((ringOfFirePos -= 0.95f) <= 0){
		ringOfFirePos += currentDistance;
		if (bigDistanceBool){
			bigDistanceBool = false;
			currentDistance = baseDistanceBig + (rand() % distanceVariation);
		}
		else{
			bigDistanceBool = true;
			currentDistance = baseDistanceSmall + (rand() % distanceVariation);
		}
	}
	/*if (--meterCounterPos<-112){
		meterCounterPos += 461;
	}*/
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleLevels::Update(){
	App->renderer->Blit(backgroundGraphics, 0, 198, &lowerBackground);
	
	if (elephantPos < 0){
		App->renderer->Blit(backgroundGraphics, elephantPos, 78, &elephantUpperBackground);
		App->renderer->Blit(backgroundGraphics, elephantPos+SCREEN_WIDTH, 78, &elephantUpperBackground);
		App->renderer->Blit(backgroundGraphics, elephantPos + elephantUpperBackground.w, 78, &upperBackground.GetCurrentFrame());
	}
	else{
		if (elephantPos + elephantUpperBackground.w > SCREEN_WIDTH){
			App->renderer->Blit(backgroundGraphics, elephantPos - SCREEN_WIDTH, 78, &elephantUpperBackground);
		}
		App->renderer->Blit(backgroundGraphics, elephantPos, 78, &elephantUpperBackground);
		App->renderer->Blit(backgroundGraphics, elephantPos + elephantUpperBackground.w, 78, &upperBackground.GetCurrentFrame());
		App->renderer->Blit(backgroundGraphics, elephantPos + elephantUpperBackground.w-SCREEN_WIDTH, 78, &upperBackground.GetCurrentFrame());
	}

	App->renderer->Blit(App->graphics->sprites, ringOfFirePos, 188, &App->graphics->bigRingOfFire.GetCurrentFrame());
	App->renderer->Blit(App->graphics->sprites, ringOfFirePos + currentDistance, 188, &App->graphics->bigRingOfFire.GetCurrentFrame());
	App->renderer->Blit(App->graphics->misc, meterCounterPos, 430, &App->graphics->meterCounter);
	//App->renderer->Blit(App->graphics->misc, meterCounterPos + 663, 188, &App->graphics->meterCounter);

	return UPDATE_CONTINUE;
}

// Postupdate: draw hud
update_status ModuleLevels::PostUpdate(){
	App->renderer->Blit(backgroundGraphics, 0, 0, &hud);

	return UPDATE_CONTINUE;
}