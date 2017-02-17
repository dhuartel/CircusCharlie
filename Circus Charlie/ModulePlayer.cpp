#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Graphics.h"
#include "ModuleRender.h"
#include "Globals.h"
#include "SDL\include\SDL.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled){
}

ModulePlayer::~ModulePlayer(){

}

bool ModulePlayer::Start(){
	status = PLAYERSTANDING;
	position.x = 100;
	position.y = 390;
	//Create Collider

	return true;
}

update_status ModulePlayer::PreUpdate(){
	switch (status)
	{
	case PLAYERSTANDING:
		LOG("EL getkey: %d", App->input->GetKey(SDL_SCANCODE_A));
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			LOG("Po zi");
			position.x -= movementSpeed;
			status = PLAYERMOVINGBACKWARDS;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			LOG("Po zi");
			position.x += movementSpeed;
			status = PLAYERMOVINGONWARDS;
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			jumpCommited = 0;
		}
		break;
	case PLAYERMOVINGONWARDS:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			position.x -= movementSpeed;
			status = PLAYERMOVINGBACKWARDS;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			position.x += movementSpeed;
		}
		else{
			status = PLAYERSTANDING;
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			jumpCommited = 0;
		}
		break;
	case PLAYERMOVINGBACKWARDS:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			position.x -= movementSpeed;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			position.x += movementSpeed;
			status = PLAYERMOVINGONWARDS;
		}
		else{
			status = PLAYERSTANDING;
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			jumpCommited = 0;
		}
		break;
	case PLAYERJUMPING:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			position.x -= movementSpeed;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			position.x += movementSpeed;
		}
		if (jumpCommited < 30){
			++jumpCommited;
			++position.y;
		}
		else if (jumpCommited < 60){
			++jumpCommited;
			--position.y;
		}
		else{
			status = PLAYERSTANDING;
		}
		break;
	}
	return UPDATE_CONTINUE;
}

update_status ModulePlayer::Update(){
	LOG("status: %d", status);
	switch (status)
	{
	case PLAYERSTANDING:
		App->renderer->Blit(App->graphics->sprites, position.x, position.y, &App->graphics->movingLionOnwards.GetFrame(0));
		App->renderer->Blit(App->graphics->sprites, position.x + 19, position.y - 50, &App->graphics->movingPlayerOnLion.GetFrame(0));
		break;
	case PLAYERMOVINGONWARDS:
		App->renderer->Blit(App->graphics->sprites, position.x, position.y, &App->graphics->movingLionOnwards.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, position.x + 19, position.y - 50, &App->graphics->movingPlayerOnLion.GetCurrentFrame());
		break;
	case PLAYERMOVINGBACKWARDS:
		App->renderer->Blit(App->graphics->sprites, position.x, position.y, &App->graphics->movingLionBackwards.GetCurrentFrame());
		App->renderer->Blit(App->graphics->sprites, position.x + 19, position.y - 50, &App->graphics->movingPlayerOnLion.GetCurrentFrame());
		break;
	}
	return UPDATE_CONTINUE;
}