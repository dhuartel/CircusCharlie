#pragma once

#include "Module.h"

class ModuleTextures : public Module{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture*);

private:
	list<SDL_Texture*> textures;
};