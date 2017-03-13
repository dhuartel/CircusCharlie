#pragma once

#include<list>
#include "Globals.h"

class Module;

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleLevels;
class ModuleInput;
class ModulePlayer;
class ModuleAudio;
class ModuleCollision;
class ModuleEnemy;
class Graphics;
class AudioEffects;

class Application{
public:
	Application();
	~Application();
	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleRender* renderer;
	ModuleLevels* levels;
	ModuleInput* input;
	ModulePlayer* player;
	ModuleAudio* audio;
	ModuleCollision* collision;
	ModuleEnemy* enemy;

	Graphics* graphics;
	AudioEffects* audioEffects;

	bool debugMode = false;

private:
	list<Module*> modules;
};

extern Application* App;