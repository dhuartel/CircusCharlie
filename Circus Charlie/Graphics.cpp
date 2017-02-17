#include "Graphics.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"

Graphics::Graphics(){
	bigRingOfFire.frames.push_back({ 289, 308, 52, 171 });
	bigRingOfFire.frames.push_back({ 351, 308, 52, 171 });
	bigRingOfFire.speed = 0.1f;

	smallRingOfFire.frames.push_back({ 82, 225, 24, 64 });
	smallRingOfFire.frames.push_back({ 109, 225, 24, 64 });

	meterCounter.x = 2;
	meterCounter.y = 0;
	meterCounter.w = 109;
	meterCounter.h = 39;

	movingLionBackwards.frames.push_back({ 498, 185, 67, 33 });
	movingLionBackwards.frames.push_back({ 426, 185, 65, 33 });
	movingLionBackwards.speed = 0.1f;

	movingLionOnwards.frames.push_back({ 498, 185, 67, 33 });
	movingLionOnwards.frames.push_back({ 349, 185, 65, 33 });
	movingLionOnwards.speed = 0.1f;

	movingPlayerOnLion.frames.push_back({ 350, 124, 31, 51 });
	movingPlayerOnLion.frames.push_back({ 388, 124, 31, 51 });
	movingPlayerOnLion.speed = 0.1f;
}

void Graphics::LoadGraphics(){
	sprites = App->textures->Load("sprites/spriteRes.png");
	misc = App->textures->Load("sprites/misc.png");
}

void Graphics::UnloadGraphics(){
	App->textures->Unload(sprites);
	App->textures->Unload(misc);
}