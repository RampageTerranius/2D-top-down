#include "EventHandler.h"
#include "Math functions.h"
#include "Globals.h"

#include <SDL.h>

void HandleEvents()
{
	// calculate all physics for all currently existing projectiles.
	allProjectiles.CalcAllProjectiles();

	// handle all player based events (reloading, recoil etc...)
	allPlayers.HandlePlayerEvents();

	// Handle all events to do with current player only (camera, facing etc...)

	// TODO: set this up to always move camera to the current player (for when dead and alive)
	currentPlayer->MoveCameraToHere();
	//allPlayers.GetPlayer("Player2")->MoveCameraToHere();

	SDL_Point point = GetMapCoordFromCursor();

	currentPlayer->directionFacing.x = static_cast <float> (point.x);
	currentPlayer->directionFacing.y = static_cast <float> (point.y);
}

InputManager::InputManager()
{
	moveUp = new CommandMoveUp();
	moveDown = new CommandMoveDown();
	moveLeft = new CommandMoveLeft();
	moveRight = new CommandMoveRight();
	fire = new CommandFireWeapon();
	reload = new CommandReloadWeapon();
	build = new CommandBuild();
	changeWeaponNext = new CommandChangeWeaponNext();
	changeWeaponLast = new CommandChangeWeaponLast();

	mouse = SDL_Point{ 0,0 };

	commands[SDLK_w] = moveUp;
	commands[SDLK_s] = moveDown;
	commands[SDLK_a] = moveLeft;
	commands[SDLK_d] = moveRight;
	commands[SDL_BUTTON_LEFT] = fire;
	commands[SDLK_r] = reload;
	commands[SDL_BUTTON_RIGHT] = build;
	commands[SDLK_e] = changeWeaponNext;
	commands[SDLK_q] = changeWeaponLast;
}

// Delete all command pointers on deconstruction.
InputManager::~InputManager()
{
	for (std::map<int, Command*>::iterator iter = commands.begin(); iter != commands.end(); iter++)
		delete iter->second;
}

SDL_Point InputManager::GetMouseLocation()
{
	return SDL_Point{ mouse.x, mouse.y };
}

// Gather the users input and maps it as required.
bool InputManager::InputToActions()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			return false;

		case SDL_KEYDOWN:		
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return false;
			OnKeyDownInput(event);
			break;

		case SDL_KEYUP:		
			OnKeyUpInput(event);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMotion(event);			
			break;

		case SDL_MOUSEBUTTONDOWN:
			OnMouseDownInput(event);
			break;

		case SDL_MOUSEBUTTONUP:
			OnMouseUpInput(event);
			break;
		}
	return true;
}

// Add all commands to a list for processing.
void InputManager::DispatchCommands(std::vector<Command*>& command_queue)
{
	for (std::map<int, Command*>::iterator iter = commands.begin(); iter != commands.end(); iter++)
		if (IsHeld(iter->first))
			command_queue.push_back(iter->second);
}

bool InputManager::GenerateInput(std::vector<Command*>& CommandVector)
{
	if (!InputToActions())
		return false;
	else
	{
		DispatchCommands(CommandVector);
		return true;
	}
}

void InputManager::OnMouseMotion(SDL_Event& event)
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
}

void InputManager::OnKeyDownInput(SDL_Event& event)
{
	state[event.key.keysym.sym] = KEYSTATE_PRESSED;
}

void InputManager::OnKeyUpInput(SDL_Event& event)
{
	state[event.key.keysym.sym] = KEYSTATE_RELEASED;
}

void InputManager::OnMouseDownInput(SDL_Event& event)
{
	state[event.button.button] = KEYSTATE_PRESSED;
}

void InputManager::OnMouseUpInput(SDL_Event& event)
{
	state[event.button.button] = KEYSTATE_RELEASED;
}

// Check if the key is currently being held.
bool InputManager::IsHeld(int key)
{
	return state[key];
}

void InputManager::Bind(int key, Command* command)
{
	commands[key] = command;
}