#include "Graphics.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"

Graphics::Graphics(){
	bigRingOfFireBack.frames.push_back({ 289, 308, 26, 171 });
	bigRingOfFireBack.frames.push_back({ 351, 308, 26, 171 });
	bigRingOfFireBack.speed = 0.1f;

	bigRingOfFireFront.frames.push_back({ 315, 308, 26, 171 });
	bigRingOfFireFront.frames.push_back({ 377, 308, 26, 171 });
	bigRingOfFireFront.speed = 0.1f;

	smallRingOfFireBack.frames.push_back({ 173, 342, 25, 136 });
	smallRingOfFireBack.frames.push_back({ 232, 342, 25, 136 });
	smallRingOfFireBack.speed = 0.1f;

	smallRingOfFireFront.frames.push_back({ 198, 342, 25, 136 });
	smallRingOfFireFront.frames.push_back({ 257, 342, 25, 136 });
	smallRingOfFireFront.speed = 0.1f;

	meterCounter.x = 0;
	meterCounter.y = 0;
	meterCounter.w = 112;
	meterCounter.h = 39;

	movingLionBackwards.frames.push_back({ 498, 185, 67, 33 });
	movingLionBackwards.frames.push_back({ 426, 185, 65, 33 });
	movingLionBackwards.speed = 0.1f;

	movingLionOnwards.frames.push_back({ 426, 185, 66, 33 });
	movingLionOnwards.frames.push_back({ 349, 185, 71, 33 });
	movingLionOnwards.speed = 0.1f;

	movingPlayerOnLion.frames.push_back({ 350, 124, 31, 51 });
	movingPlayerOnLion.frames.push_back({ 388, 124, 31, 51 });
	movingPlayerOnLion.speed = 0.1f;

	deadLion.x = 579;
	deadLion.y = 185;
	deadLion.w = 67;
	deadLion.h = 33;

	deadPlayerOnLion.x = 349;
	deadPlayerOnLion.y = 68;
	deadPlayerOnLion.w = 33;
	deadPlayerOnLion.h = 51;

	numbers.frames.push_back({ 113, 0, 18, 15 });//0
	numbers.frames.push_back({ 131, 0, 18, 15 });//1
	numbers.frames.push_back({ 149, 0, 18, 15 });//2
	numbers.frames.push_back({ 113, 15, 18, 15 });//3
	numbers.frames.push_back({ 131, 15, 18, 15 });//4
	numbers.frames.push_back({ 149, 15, 18, 15 });//5
	numbers.frames.push_back({ 113, 30, 18, 15 });//6
	numbers.frames.push_back({ 131, 30, 18, 15 });//7
	numbers.frames.push_back({ 149, 30, 18, 15 });//8
	numbers.frames.push_back({ 113, 45, 18, 15 });//9
	numbers.speed = 0.01f;
}

void Graphics::LoadGraphics(){
	sprites = App->textures->Load("sprites/spriteRes.png");
	misc = App->textures->Load("sprites/misc.png");
}

void Graphics::UnloadGraphics(){
	App->textures->Unload(sprites);
	App->textures->Unload(misc);
}