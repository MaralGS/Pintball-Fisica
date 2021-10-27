#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = map = ball = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Fonts
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("pinball/fonts.png", lookupTable, 2);

	App->renderer->camera.x = App->renderer->camera.y = 0;

	Ball = App->physics->CreateCircle(positionPX, positionPY, 14);
	Ball->listener = this;
	Ball->body->SetBullet(true);


	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	EndScreen = App->textures->Load("pinball/End_Screen.png");
	ball = App->textures->Load("Pinball/Poro_Coin.png");
	map = App->textures->Load("pinball/Pinball_Map.png");
	

	//sound
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	Push_fx = App->audio->LoadFx("pinball/Push_Ball.wav");

	// fonts
	Fonts = App->textures->Load("pinball/fonts.png");
	
	//sensor
	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);
	Loose = App->physics->CreateRectangleSensor(218, 1030, 80, 150,0);
	Rebot = App->physics->CreateRectangleSensor(132, 727, 160, 6, 20);
	Rebot2 = App->physics->CreateRectangleSensor(315, 727, 160, 6, -20);
	//Loose = App->physics->CreateRectangleSensor(218, 780, 80, 150);
	circle1 = App->physics->CreateCircleSensor(220, 87, 49);
	circle2 = App->physics->CreateCircleSensor(152, 378, 42);
	circle3 = App->physics->CreateCircleSensor(293, 378, 42);
	circle4 = App->physics->CreateCircleSensor(223, 490, 42);

	//audio sensors
	Push_Sensor = App->physics->CreateRectangleSensor(485, 900, 10, 5, 0);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	App->renderer->Blit(map, 0, 0, NULL);
	
	
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		Ball->body->SetTransform(b2Vec2(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY())), 0);
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 14));
	}
	
	

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}	
	
	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		b2Vec2 F = b2Vec2(0, -1000);
		App->physics->RecE->body->ApplyForceToCenter(F, 1);
	}	
	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		b2Vec2 F = b2Vec2(0, -1000);
		App->physics->RecD->body->ApplyForceToCenter(F, 1);
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		b2Vec2 F = b2Vec2(0, -500);
		App->physics->Barup->body->ApplyForceToCenter(F, 0);
	}

	if(App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		if (Finish_End = true)
		{
		vidas = 3;
		score = 0;
		Ball->body->SetTransform(b2Vec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(930)), 0);
		Ball->body->SetAngularVelocity(0);
		Ball->body->SetLinearVelocity(b2Vec2(0, 0));
		
		Finish_End = false;
		}
		
		
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();
	
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}


	
		int x, y;
		Ball->GetPosition(x,y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f,Ball->GetRotation());
		if (ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if (hit >= 0)
				ray_hit = hit;
		}
	

	

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	if (vidas <= 0)
	{
		App->renderer->Blit(EndScreen, 0, 0, NULL);
		Finish_End = true;
	}
	
	/*if (score = score + 100)
	{
		vidas++;
		score++;
	}*/

	if (App->physics->PAudio == true)
	{
		App->audio->PlayFx(bonus_fx);
		App->physics->PAudio = false;
	}
	if (death == true) {
		Ball->body->SetTransform(b2Vec2(PIXEL_TO_METERS(500), PIXEL_TO_METERS(930)), 0);
		Ball->body->SetAngularVelocity(0);
		Ball->body->SetLinearVelocity(b2Vec2(0, 0));
		death = false;
	}

	sprintf_s(scoreText, "pts%6d", score);
	App->fonts->DrawTxt(320, 920, scoreFont, scoreText);
	sprintf_s(scoreText,"ph %3d", vidas);
	App->fonts->DrawTxt(30, 920, scoreFont, scoreText);

	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);
	

}
