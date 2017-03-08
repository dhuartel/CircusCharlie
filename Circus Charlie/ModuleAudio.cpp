#include "Application.h"
#include "Globals.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

using namespace std;

ModuleAudio::ModuleAudio(bool start_enabled) : Module(start_enabled){

}

ModuleAudio::~ModuleAudio(){

}

bool ModuleAudio::Init(){
	bool ret = true;
	LOG("Loading audio mixer");
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0){
		LOG("Error initializing audio subsystem, SDL_Error: %s",SDL_GetError());
		ret = false;
	}

	//Load support for ogg
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if (flags != init){
		LOG("Error loading support for OGG, SDL_Error:%s", SDL_GetError());
		ret = false;
	}

	//Initialize SDL_Mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		LOG("Error initializing audio mixer, Mix_Error: %s", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::CleanUp(){
	LOG("Freeing sound FX, closing mixer and audio subsystem");

	if (music != nullptr){
		Mix_FreeMusic(music);
	}

	for (vector<Mix_Chunk*>::iterator it = fx.begin(); it != fx.end(); ++it){
		Mix_FreeChunk(*it);
	}
	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

bool ModuleAudio::PlayMusic(const char* path, float fade_time){
	bool ret = true;
	if (music != nullptr){
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music=Mix_LoadMUS(path);
	if (music == nullptr){
		LOG("Error loading music, Mix_Error: %s", Mix_GetError());
		ret = false;
	}
	else{
		if (fade_time > 0.0f){
			if (Mix_FadeInMusic(music,-1,(int)(fade_time*1000.0f)) < 0){
				LOG("Error fading in music, Mix_Error: %s", Mix_GetError());
				ret = false;
			}
		}
		else{
			if (Mix_PlayMusic(music, -1) < 0){
				LOG("Error playing music, Mix_Error: %s", Mix_GetError());
				ret = false;
			}
		}
	}
	return ret;
}

unsigned int ModuleAudio::LoadFx(const char* path){
	unsigned int ret = 0;
	Mix_Chunk* chunk=Mix_LoadWAV(path);
	if (chunk == nullptr){
		LOG("Error loading waw, Mix_Error: %s", Mix_GetError());
		ret = false;
	}
	else{
		fx.push_back(chunk);
		ret = fx.size() - 1;
	}
	return ret;
}

bool ModuleAudio::PlayFx(unsigned int id, int repeat){
	bool ret = false;
	if (id < fx.size()){
		if (Mix_PlayChannel(-1, fx[id], repeat) < 0){
			LOG("Error playing wav, Mix_Error: %s", Mix_GetError());
		}
		else{
			ret = true;
		}
	}
	return ret;
}