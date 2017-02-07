#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures(){

}

ModuleTextures::~ModuleTextures(){

}

bool ModuleTextures::Init(){
	bool ret = true;
	LOG("Init image library");

	//Load dynamic library for pngs
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if (init != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleTextures::CleanUp(){
	bool ret = true;
	LOG("Freeing textures and image library");

	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it){
		SDL_DestroyTexture(*it);
	}

	textures.clear();
	IMG_Quit();

	return ret;
}

SDL_Texture* const ModuleTextures::Load(const char* path){
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == nullptr){
		LOG("Error loading the surface from path:%s, SDL_Error: %s", path, IMG_GetError());
	}
	else{
		texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);

		if (texture == nullptr){
			LOG("Texture couldn't be created from surface, SDL_Error: %s\n", SDL_GetError());
		}
		else{
			textures.push_back(texture);
		}
		SDL_FreeSurface(surface);
	}

	return texture;
}

void ModuleTextures::Unload(SDL_Texture* texture){
	for (list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it){
		if (*it == texture){
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}