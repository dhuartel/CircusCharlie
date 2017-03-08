#pragma once

#include <vector>
#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;//background music
struct Mix_Chunk;//sound fx

class ModuleAudio : public Module{
public:
	ModuleAudio(bool start_enabled=true);
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

private://Variables

	_Mix_Music*	music = nullptr;
	std::vector<Mix_Chunk*>	fx;
};