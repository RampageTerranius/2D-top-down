#include "Main.h"

#include "Globals.h"

#include <SDL.h>

int main(int argc, char* argv[])
{
	// Run setup.
	running = SetupEngine();

	SDL_Event event;

	while (running)
	{
		EventHandle(event);

		Render();
	}

	ShutdownEngine();

	return 1;
}
