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
}

void Graphics::LoadGraphics(){
	sprites = App->textures->Load("sprites/spriteRes.png");
}

void Graphics::UnloadGraphics(){
	App->textures->Unload(sprites);
}