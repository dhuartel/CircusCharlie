#pragma once

#include "Module.h"
#include "Point.h"

#include "SDL/include/SDL_scancode.h"

enum EventWindow{
	EW_QUIT = 0,
	EW_HIDE = 1,
	EW_SHOW = 2,
	EW_COUNT
};

enum KeyState{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module{
public:
	ModuleInput();
	~ModuleInput();
	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	KeyState GetKey(int id) const{
		return keyboard[id];
	}

	bool GetWindowEvent(EventWindow id) const;

private:
	bool windowEvents[EW_COUNT];
	KeyState* keyboard;
};