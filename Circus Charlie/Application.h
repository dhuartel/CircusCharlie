#pragma once

#include<list>
#include "Globals.h"

class Module;

class ModuleRender;
class ModuleWindow;
class ModuleTextures; 

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

	bool debugMode = false;

private:
	list<Module*> modules;
};

extern Application* App;