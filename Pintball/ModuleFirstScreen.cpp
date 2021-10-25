#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleFirstScreen.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"

ModuleFirstScreen::ModuleFirstScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	Title = NULL;
	sensed2 = false;
}

ModuleFirstScreen::~ModuleFirstScreen()
{}

// Load assets
bool ModuleFirstScreen::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	Title = App->textures->Load("pinball/First_Screen.png");

	return ret;
}

// Load assets
bool ModuleFirstScreen::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleFirstScreen::Update()
{
	App->renderer->Blit(Title, 0, 0, NULL);
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_intro, 90);
	}
	return UPDATE_CONTINUE;
}


void ModuleFirstScreen::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}
