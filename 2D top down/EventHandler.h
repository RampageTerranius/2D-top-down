#pragma once

#include "Character.h"

#include <string>
#include <map>
#include <vector>

// With help from the following sources:
// https://gameprogrammingpatterns.com/command.html
// https://codereview.stackexchange.com/questions/55365/input-handling-system-using-the-command-pattern

enum KeyState
{	
	KEYSTATE_RELEASED = false,
	KEYSTATE_PRESSED = true
};

class Command
{
public:
	virtual ~Command() {};
	virtual void Execute(Player* player) = 0;
};

class CommandFireWeapon : public Command
{
public:
	void Execute(Player* player) { player->FireWeapon(); }
};

class CommandReloadWeapon : public Command
{
public:
	void Execute(Player* player) { player->ReloadWeapon(); }
};

class CommandBuild : public Command
{
public:
	void Execute(Player* player) {  }
};

class CommandChangeWeaponNext : public Command
{
public:
	void Execute(Player* player) { player->SwitchToNextWeapon(); }
};

class CommandChangeWeaponLast : public Command
{
public:
	void Execute(Player* player) { player->SwitchToLastWeapon(); }
};

class CommandMoveUp : public Command
{
public:
	void Execute(Player* player) { player->MoveBy(0, -player->currentMovementVel); }
};

class CommandMoveDown : public Command
{
public:
	void Execute(Player* player) { player->MoveBy(0, player->currentMovementVel); }
};

class CommandMoveLeft : public Command
{
public:
	void Execute(Player* player) { player->MoveBy(-player->currentMovementVel, 0); }
};

class CommandMoveRight : public Command
{
public:
	void Execute(Player* player) { player->MoveBy(player->currentMovementVel, 0); }
};

class InputManager
{
public:
	~InputManager();
	InputManager();
	bool GenerateInput(std::vector<Command*>& commandVector);
	void Bind(int key, Command* command);
	SDL_Point GetMouseLocation();

private:
	// Basic command Pointers.
	Command* moveUp;
	Command* moveDown;
	Command* moveLeft;
	Command* moveRight;
	Command* fire;
	Command* reload;
	Command* build;
	Command* changeWeaponNext;
	Command* changeWeaponLast;

	// Commands and keystates.
	std::map <int, Command*> commands;
	std::map <int, KeyState> state;
	std::map <int, KeyState> previousState;

	SDL_Point mouse;

	bool InputToActions();
	void DispatchCommands(std::vector<Command*>& command_queue);

	void OnKeyDownInput(SDL_Event& event);
	void OnKeyUpInput(SDL_Event& event);

	void OnMouseMotion(SDL_Event& event);
	void OnMouseDownInput(SDL_Event& event);
	void OnMouseUpInput(SDL_Event& event);

	bool IsHeld(int key);
};

void HandleEvents();