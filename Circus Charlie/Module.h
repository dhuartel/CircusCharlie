#pragma once

#include "Globals.h"

class Application;
class Collider;

class Module{

public:
	Module(bool active=true): active(active){}

	virtual ~Module(){}

	bool IsEnabled() const { return active; }

	bool Enable(){
		if (!active){
			return active = Start();
		}
		return true;
	}

	bool Disable(){
		if (active){
			return active = !CleanUp();
		}
		return true;
	}

	virtual bool Init(){ return true; }//Initialization of module

	virtual bool Start(){ return true; }//Function called when enabling the module

	virtual bool CleanUp(){ return true; }//Function called when disabling the module to clean and avoid memory leaks

	virtual update_status PreUpdate(){ return UPDATE_CONTINUE; }

	virtual update_status Update(){ return UPDATE_CONTINUE; }

	virtual update_status PostUpdate(){ return UPDATE_CONTINUE; }

	virtual void OnCollision(Collider*, Collider*){}//Each module has to manage its collisions separately

private:
	bool active = true;
};