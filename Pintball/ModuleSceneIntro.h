#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	
public:
	int vidas = 3;
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> balls;
	



	PhysBody* sensor;
	PhysBody* Loose;
	PhysBody* Rebot;
	PhysBody* Rebot2;
	PhysBody* Ball;
	PhysBody* circle1;
	PhysBody* circle2;
	PhysBody* circle3;
	PhysBody* circle4;
	PhysBody* Push_Sensor;
	PhysBody* Stick_LEFT;
	bool sensed;
	bool death;
	int positionPX = 488;
	int positionPY = 940;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* EndScreen;
	SDL_Texture* map;
	SDL_Texture* ball;
	SDL_Texture* Fonts;
	bool FTitle = true;
	bool Finish_End = false;

	//Fonts
	uint score = 000;
	int scoreFont = -1;
	char scoreText[150] = { "\0" };

	uint bonus_fx;
	uint Push_fx;
	p2Point<int> ray;
	bool ray_on;
};
