#include "Main.h"

#include "Globals.h"

#include <SDL.h>

void CalculateFPS()
{
	Uint32 frametimesindex;
	Uint32 getticks;
	Uint32 count;

	frametimesindex = totalFramesCounted % FRAME_TIMERS;

	getticks = SDL_GetTicks();

	frametimes[frametimesindex] = getticks - frametimelast;

	frametimelast = getticks;

	if (totalFramesCounted < FRAME_TIMERS)
		count = totalFramesCounted;
	else
		count = FRAME_TIMERS;

	totalFramesCounted++;

	// add up all the values and divide to get the average frame time.
	avgFPS = 0;
	for (Uint32 i = 0; i < count; i++)
		avgFPS += frametimes[i];	

	avgFPS /= count;

	// now to make it an actual frames per second value...
	avgFPS = 1000.f / avgFPS;	
}

int main(int argc, char* argv[])
{
	// Run setup.
	bool running = true;

	running = SetupEngine();	

	std::vector<Command*> CommandList;
	
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
		
		CalculateFPS();

		Render();		

		if (capFrameRate)
		{
			int frameTicks = capTimer.GetTicks();
			if (frameTicks < ticksPerFrame)
				SDL_Delay(ticksPerFrame - frameTicks);
		}
	}

	// Shutdown the engine.
	ShutdownEngine();

	return 1;
}
