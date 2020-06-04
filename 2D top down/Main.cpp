#include "Main.h"

#include "Globals.h"

#include <SDL.h>

int main(int argc, char* argv[])
{
	// Run setup.
	bool running = true;

	running = SetupEngine();	

	std::vector<Command*> CommandList;

	fpsTimer.Start();

	int countedFrames = 0;

	while (running)
	{		
		capTimer.Start();

		running = iManager->GenerateInput(CommandList);

		while (!CommandList.empty())
		{
			CommandList.back()->Execute(currentPlayer);
			CommandList.pop_back();
		}

		HandleEvents();

		avgFPS = countedFrames / (fpsTimer.GetTicks() / 1000.f);
		if (avgFPS > 2000000)		
			avgFPS = 0;		

		Render();

		countedFrames++;

		int frameTicks = capTimer.GetTicks();
		if (frameTicks < ticksPerFrame)
			SDL_Delay(ticksPerFrame - frameTicks);
	}

	// Shutdown the engine.
	ShutdownEngine();

	return 1;
}
