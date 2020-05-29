#include "Main.h"

#include "Globals.h"

#include <SDL.h>

int main(int argc, char* argv[])
{
	// Run setup.
	bool running = true;

	running = SetupEngine();	

	std::vector<Command*> CommandList;

	while (running)
	{
		running = iManager->GenerateInput(CommandList);

		while (!CommandList.empty())
		{
			CommandList.back()->Execute(testPlayer);
			CommandList.pop_back();
		}

		Render();
	}

	ShutdownEngine();

	return 1;
}
