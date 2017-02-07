#include "Application.h"
#include "ModuleLevels.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

ModuleLevels::ModuleLevels(bool start_enabled) : Module(start_enabled){
	lowerBackground.x = 0;
	lowerBackground.y = 0;
	lowerBackground.w = 636;
	lowerBackground.h = 279;


	upperBackground.x = 0;
	upperBackground.y = 0;
	upperBackground.w = 636;//679
	upperBackground.h = 120;

	hud.x = 0;
	hud.y = 0;
	hud.w = 636;
	hud.h = 78;

	//636x477
}

ModuleLevels::~ModuleLevels(){}

//Load textures, set camera and enable other modules 
bool ModuleLevels::Start(){
	lowerBackgroundGraphics = App->textures->Load("background/greenBackground.png");
	upperBackgroundGraphics = App->textures->Load("background/upperBackground.png");
	hudGraphics = App->textures->Load("background/hud.png");

	//Set the camera to its position
	//App->renderer->camera.y = 20 * SCREEN_SIZE;

	return true;
}

//Unload textures
bool ModuleLevels::CleanUp()
{
	LOG("Unloading levels scene");

	App->textures->Unload(lowerBackgroundGraphics);
	App->textures->Unload(upperBackgroundGraphics);
	App->textures->Unload(hudGraphics);

	return true;
}

// Update: draw background
update_status ModuleLevels::Update()
{
	App->renderer->Blit(lowerBackgroundGraphics, 0, 198, &lowerBackground);
	App->renderer->Blit(upperBackgroundGraphics, 0, 78, &upperBackground);

	return UPDATE_CONTINUE;
}

// Postupdate: draw hud
update_status ModuleLevels::PostUpdate()
{
	App->renderer->Blit(hudGraphics, 0, 0, &hud);

	return UPDATE_CONTINUE;
}