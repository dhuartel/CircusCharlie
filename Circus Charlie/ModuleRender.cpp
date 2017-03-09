#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender(){
	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
}

ModuleRender::~ModuleRender(){
}

bool ModuleRender::Init(){
	LOG("Creating Renderer context");

	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC){
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	if (renderer == nullptr){
		LOG("Error creating renderer, SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	return ret;
}

update_status ModuleRender::PreUpdate(){
	update_status ret = UPDATE_CONTINUE;
	if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0){
		ret = UPDATE_ERROR;
		LOG("Render draw color couldn't be set");
	}
	else if (SDL_RenderClear(renderer) != 0){
		ret = UPDATE_ERROR;
		LOG("Render couldn't be cleared");
	}
	return ret;
}

update_status ModuleRender::Update(){
	//Here camera will be moved when debug mode and input are implemented
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate(){
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp(){
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, int alpha){
	bool ret = true;
	if (SDL_SetTextureAlphaMod(texture, alpha) != 0){
		ret = false;
		LOG("Error setting alpha texture mod")
	}
	SDL_Rect rect;//The rect that will have the real x,y,w and h after being modified by screen size, camera position and speed  
	rect.x = (int)(camera.x*speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y*speed) + y * SCREEN_SIZE;

	if (section != NULL){
		rect.w = section->w;
		rect.h = section->h;
	}
	else{
		LOG("Querying texture");
		if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0){
			ret = false;
			LOG("Error querying texture %s", SDL_GetError());
		}
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::DrawRect(SDL_Rect rect, int r, int g, int b, int a){
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_Rect aux;
	aux.x = camera.x + rect.x*SCREEN_SIZE;
	aux.y = camera.y + rect.y*SCREEN_SIZE;
	aux.w = rect.w*SCREEN_SIZE;
	aux.h = rect.h*SCREEN_SIZE;
	SDL_RenderFillRect(renderer, &aux);
}