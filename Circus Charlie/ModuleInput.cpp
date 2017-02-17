#include "ModuleInput.h"
#include "Application.h"
#include "Globals.h"
#include "SDL\include\SDL.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(){
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState)*MAX_KEYS);
}

ModuleInput::~ModuleInput(){
	RELEASE_ARRAY(keyboard);
}

bool ModuleInput::Init(){
	LOG("Init SDL input event system");
	bool ret = true;
	//Testing
	if (SDL_Init(SDL_INIT_EVENTS) != 0){
		LOG("Error initializing SDL_Events, SDL_Error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleInput::PreUpdate(){
	static SDL_Event event;

	memset(windowEvents, false, EW_COUNT*sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i){
		if (keys[i]){
			if (keyboard[i] == KEY_IDLE){
				keyboard[i] = KEY_DOWN;
			}
			else{
				keyboard[i] = KEY_REPEAT;
			}
		}
		else{
			if (keyboard[i] == KEY_DOWN || keyboard[i] == KEY_REPEAT){
				keyboard[i] = KEY_UP;
			}
			else{
				keyboard[i] = KEY_IDLE;
			}
		}
	}

	while (SDL_PollEvent(&event) != NULL){
		switch (event.type){
			case SDL_QUIT:
				windowEvents[EW_QUIT] = true;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event){
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						windowEvents[EW_SHOW] = true;
					break;

					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_FOCUS_LOST:
						windowEvents[EW_HIDE] = true;
				}
		}
	}

	if (windowEvents[EW_QUIT] || keys[SDL_SCANCODE_ESCAPE]){
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp(){
	LOG("Quittin SDL event system");
	//Testing
	SDL_Quit();
	return true;
}

bool ModuleInput::GetWindowEvent(EventWindow id) const{
	return windowEvents[id];
}