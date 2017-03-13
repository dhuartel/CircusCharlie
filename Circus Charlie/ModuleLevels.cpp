#include "Application.h"
#include "ModuleLevels.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleEnemy.h"
#include "Graphics.h"

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

	App->audio->PlayMusic("audio/music/stage1_4.ogg");

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
	//Debug---------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_F)){
		upperBackground.loop = true;
	}
	//---------------------------------------------

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

	MeterDrawer();
	

	return UPDATE_CONTINUE;
}

// Postupdate: draw hud and front part of fire rings
update_status ModuleLevels::PostUpdate(){
	App->renderer->Blit(backgroundGraphics, 0, 0, &hud);
	return UPDATE_CONTINUE;
}

void ModuleLevels::MovingPlayer(bool onwards, float speed){
	if (onwards){
		elephantPos -= speed;
		if (elephantPos < 0 - elephantUpperBackground.w){
			elephantPos = SCREEN_WIDTH - elephantUpperBackground.w;
		}
		meterCounterPos -= speed;
		if (meterCounterPos<-112){
			metersLeft -= 1;
			meterCounterPos += SCREEN_WIDTH;
		}
	}
	else{
		elephantPos += speed;
		if (elephantPos > SCREEN_WIDTH){
			elephantPos = 0;
		}
		meterCounterPos += speed;
		if (meterCounterPos>SCREEN_WIDTH){
			meterCounterPos -= SCREEN_WIDTH;
			metersLeft += 1;
		}
	}
	App->enemy->Moving(onwards, speed);
}

void ModuleLevels::MeterDrawer(){
	App->renderer->Blit(App->graphics->misc, meterCounterPos, 430, &App->graphics->meterCounter);
	App->renderer->Blit(App->graphics->misc, meterCounterPos + SCREEN_WIDTH, 430, &App->graphics->meterCounter);
	App->renderer->Blit(App->graphics->misc, meterCounterPos - SCREEN_WIDTH, 430, &App->graphics->meterCounter);
	App->renderer->Blit(App->graphics->misc, meterCounterPos + 58, 430 + 13, &App->graphics->numbers.GetFrame(0));
	App->renderer->Blit(App->graphics->misc, meterCounterPos + SCREEN_WIDTH + 58, 430 + 13, &App->graphics->numbers.GetFrame(0));
	App->renderer->Blit(App->graphics->misc, meterCounterPos - SCREEN_WIDTH + 58, 430 + 13, &App->graphics->numbers.GetFrame(0));
	if (metersLeft > 9){
		App->renderer->Blit(App->graphics->misc, meterCounterPos + 16, 430 + 13, &App->graphics->numbers.GetFrame(metersLeft / 10));
		App->renderer->Blit(App->graphics->misc, meterCounterPos + 37, 430 + 13, &App->graphics->numbers.GetFrame(metersLeft % 10));
	}
	else{
		App->renderer->Blit(App->graphics->misc, meterCounterPos + 37, 430 + 13, &App->graphics->numbers.GetFrame(metersLeft));
	}

	int aux = metersLeft + 1;
	if (aux > 9){
		App->renderer->Blit(App->graphics->misc, meterCounterPos - SCREEN_WIDTH + 16, 430 + 13, &App->graphics->numbers.GetFrame(aux / 10));
		App->renderer->Blit(App->graphics->misc, meterCounterPos - SCREEN_WIDTH + 37, 430 + 13, &App->graphics->numbers.GetFrame(aux % 10));
	}
	else{
		App->renderer->Blit(App->graphics->misc, meterCounterPos - SCREEN_WIDTH + 37, 430 + 13, &App->graphics->numbers.GetFrame(aux));
	}

	aux = metersLeft - 1;
	if (aux > 9){
		App->renderer->Blit(App->graphics->misc, meterCounterPos + SCREEN_WIDTH + 16, 430 + 13, &App->graphics->numbers.GetFrame(aux / 10));
		App->renderer->Blit(App->graphics->misc, meterCounterPos + SCREEN_WIDTH + 37, 430 + 13, &App->graphics->numbers.GetFrame(aux % 10));
	}
	else{
		App->renderer->Blit(App->graphics->misc, meterCounterPos + SCREEN_WIDTH + 37, 430 + 13, &App->graphics->numbers.GetFrame(aux));
	}
}

