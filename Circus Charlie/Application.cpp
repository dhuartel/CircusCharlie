#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleLevels.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "Graphics.h"

using namespace std;

Application::Application(){
	//Order matters, as it determines init, update and cleanup orders
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(levels = new ModuleLevels());
	modules.push_back(player = new ModulePlayer());
	modules.push_back(renderer = new ModuleRender());
	graphics = new Graphics();
}

Application::~Application(){
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init(){
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not enabled

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	graphics->LoadGraphics();
	return ret;
}

update_status Application::Update(){
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp(){
	bool ret = true;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	graphics->UnloadGraphics();
	return ret;
}