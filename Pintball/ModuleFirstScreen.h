#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleFirstScreen : public Module
{
public:
	ModuleFirstScreen(Application* app, bool start_enabled = true);
	~ModuleFirstScreen();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	PhysBody* Loose;
	SDL_Texture* Title;
	bool sensed2;
	bool FTitle = true;
};
