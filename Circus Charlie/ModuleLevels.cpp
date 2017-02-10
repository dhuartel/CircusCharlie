#include "Application.h"
#include "ModuleLevels.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

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

	upperBackground.frames.push_back({ 84, 198, 552, 120 });
	upperBackground.frames.push_back({ 84, 78, 552, 120 });
	upperBackground.speed = 0.01f;

	hud.x = 0;
	hud.y = 0;
	hud.w = 636;
	hud.h = 78;

	//636x477 597
}

ModuleLevels::~ModuleLevels(){}

//Load textures, set camera and enable other modules 
bool ModuleLevels::Start(){
	backgroundGraphics = App->textures->Load("background/backgroundFile.png");

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
	if (App->input->GetKey(SDL_SCANCODE_LEFT)){
		if (--elephantPos < 0 - elephantUpperBackground.w){
			elephantPos = SCREEN_WIDTH - elephantUpperBackground.w;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT)){
		if (++elephantPos > SCREEN_WIDTH){
			elephantPos = 0;
		}
	}
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

	return UPDATE_CONTINUE;
}

// Postupdate: draw hud
update_status ModuleLevels::PostUpdate(){
	App->renderer->Blit(backgroundGraphics, 0, 0, &hud);

	return UPDATE_CONTINUE;
}