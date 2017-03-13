#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Graphics.h"
#include "ModuleRender.h"
#include "Globals.h"
#include "ModuleLevels.h"
#include "AudioEffects.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled){
}

ModulePlayer::~ModulePlayer(){

}

bool ModulePlayer::Start(){
	status = PLAYERSTANDING;
	startHeight = 390;
	position.x = 100;
	position.y = startHeight;

	//Create Collider
	SDL_Rect aux;
	aux.x = 0;
	aux.y = 0;
	aux.w = 0;
	aux.h = 0;
	myCollider = App->collision->CreateCollider(aux, this, PLAYER);
	return true;
}

update_status ModulePlayer::PreUpdate(){
	switch (status)
	{
	case PLAYERSTANDING:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			App->levels->MovingPlayer(false, movementSpeed);
			status = PLAYERMOVINGBACKWARDS;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			App->levels->MovingPlayer(true, movementSpeed);
			status = PLAYERMOVINGONWARDS;
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			App->audioEffects->PlayFX(JUMP);
			jumpCommited = 0;
		}
		break;
	case PLAYERMOVINGONWARDS:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			App->levels->MovingPlayer(false, movementSpeed);
			status = PLAYERMOVINGBACKWARDS;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			App->levels->MovingPlayer(true, movementSpeed);
		}
		else{
			status = PLAYERSTANDING;
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			App->audioEffects->PlayFX(JUMP);
			jumpCommited = 0;
		}
		break;
	case PLAYERMOVINGBACKWARDS:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			App->levels->MovingPlayer(false, movementSpeed);
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			App->levels->MovingPlayer(true, movementSpeed);
			status = PLAYERMOVINGONWARDS;
		}
		else{
			status = PLAYERSTANDING;
		}
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN){
			status = PLAYERJUMPING;
			App->audioEffects->PlayFX(JUMP);
			jumpCommited = 0;
		}
		break;
	case PLAYERJUMPING:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
			App->levels->MovingPlayer(false, movementSpeed);
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			App->levels->MovingPlayer(true, movementSpeed);
		}
		if (jumpCommited < 119){
			//LOG("Menos de mitad jumpSpeed: %f, acceleration: %f,\n positionY: %f,jumpCommited: %f", jumpSpeed, jumpAceleration,position.y,jumpCommited);


			jumpCommited+=jumpSpeed;
			position.y -= jumpSpeed;
			jumpSpeed += jumpAceleration;
			if (jumpCommited > 119)
				jumpSpeed = 0;
		}
		else if (jumpCommited < 238){
			///LOG("Mas de mitad jumpSpeed: %f, acceleration: %f,\n positionY: %f,jumpCommited: %f", jumpSpeed, jumpAceleration, position.y, jumpCommited);


			jumpCommited -= jumpSpeed;
			position.y -= jumpSpeed;
			jumpSpeed += jumpAceleration;
		}
		else{
			jumpSpeed = 6.0f;
			jumpCommited = 0;
			position.y = startHeight;
			status = PLAYERSTANDING;
		}
		break;
	}

	//DEBUG---------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN){
		status = PLAYERDEAD;
	}
	//----------------------------------------------------
	return UPDATE_CONTINUE;
}

update_status ModulePlayer::Update(){
	switch (status)
	{
	case PLAYERSTANDING:
		App->renderer->Blit(App->graphics->sprites, position.x, position.y, &App->graphics->movingLionBackwards.GetFrame(0));
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
	case PLAYERJUMPING:
		App->renderer->Blit(App->graphics->sprites, position.x, position.y, &App->graphics->movingLionOnwards.GetFrame(1));
		App->renderer->Blit(App->graphics->sprites, position.x + 19, position.y - 50, &App->graphics->movingPlayerOnLion.GetFrame(0));
		break;
	case PLAYERDEAD:
		App->renderer->Blit(App->graphics->sprites, position.x, position.y, &App->graphics->deadLion);
		App->renderer->Blit(App->graphics->sprites, position.x + 17, position.y - 51, &App->graphics->deadPlayerOnLion);
		break;
	}
	myCollider->collisionBox.x = position.x;
	myCollider->collisionBox.y = position.y;
	myCollider->collisionBox.w = App->graphics->deadLion.w;
	myCollider->collisionBox.h = App->graphics->deadLion.h;
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* col1, Collider* col2){
	if (col1->type == PLAYER){
		if (col2->type == HARM){
			status = PLAYERDEAD;
		}
	}
	if (col1->type == HARM){
		if (col2->type == PLAYER){
			status = PLAYERDEAD;
		}
	}
}