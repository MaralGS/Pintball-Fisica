#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "Application.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

double CtimeDif(clock_t t1, clock_t t2)
{
	float Dtick = t2 - t1;
	float Dms = (Dtick / 1000);
	return Dms;
}


int main(int argc, char ** argv)
{
	LOG("Starting game '%s'...", TITLE);
	float dt = 1.0 / 60.0;
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	
	
	while (state != MAIN_EXIT)
	{
		clock_t start = clock();
		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:
			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			
			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
		clock_t end = clock();
		float CelapsetTime = CtimeDif(start, end);
		if (dt - CelapsetTime > 0.0f) {
		Sleep(dt - CelapsetTime);
		}
	}

	delete App;
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}