#include "Main.h"

#include "Globals.h"

#include <SDL.h>

int main(int argc, char* argv[])
{
	// Run setup.
	running = Setup();

	SDL_Event event;

	while (running)
	{
		EventHandle(event);

		Render();
	}

	Shutdown();

	return 1;
}
