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
	KEYSTATE_PRESSED = true,
	KEYSTATE_RELEASED = false
};

enum ActionState
{
	ACTIONSTATE_EXECUTE = true,
	ACTIONSTATE_STOP = false
};

enum InputType
{
	INPUTTYPE_UNDEFINED,
	INPUTTYPE_ACTION,
	INPUTTYPE_STATE,
	INPUTTYPE_RANGE
};

class Command
{
public:
	virtual ~Command() {};
	virtual void Execute(Player* player) = 0;
	virtual InputType GetInputType() = 0;
};

class CommandFireWeapon : public Command
{
public:
	void Execute(Player* player) { player->FireWeapon(); }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandReloadWeapon : public Command
{
public:
	void Execute(Player* player) { player->ReloadWeapon(); }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandBuild : public Command
{
public:
	void Execute(Player* player) {  }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandChangeWeaponNext : public Command
{
public:
	void Execute(Player* player) { player->SwitchToNextWeapon(); }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandChangeWeaponLast : public Command
{
public:
	void Execute(Player* player) { player->SwitchToLastWeapon(); }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandMoveUp : public Command
{
public:
	void Execute(Player* player) {  }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandMoveDown : public Command
{
public:
	void Execute(Player* player) {  }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandMoveLeft : public Command
{
public:
	void Execute(Player* player) {  }
	InputType GetInputType() { return INPUTTYPE_STATE; }
};

class CommandMoveRight : public Command
{
public:
	void Execute(Player* player) {  }
	InputType GetInputType() { return INPUTTYPE_STATE; }
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
	std::map <int, ActionState> action;

	SDL_Point mouse;

	bool InputToActions();
	void DispatchCommands(std::vector<Command*>& command_queue);

	void OnKeyDownInput(SDL_Event& event);
	void OnKeyUpInput(SDL_Event& event);

	void OnMouseMotion(SDL_Event& event);
	void OnMouseDownInput(SDL_Event& event);
	void OnMouseUpInput(SDL_Event& event);

	bool IsHeld(int key);
	bool WasPressed(int key);
};