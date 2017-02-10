#pragma once

#include<list>
#include "Globals.h"

class Module;

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleLevels;
class ModuleInput;

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

	bool debugMode = false;

private:
	list<Module*> modules;
};

extern Application* App;