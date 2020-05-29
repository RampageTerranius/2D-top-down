#include "EventHandle.h"

#include "Globals.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Entity.h"
#include "Projectile.h"

#include "Math functions.h"

#include <SDL.h>

// Handles all keyboard/mouse events.
void EventHandle(SDL_Event& event)
{
	// Update all our structures handling what buttons are held down currently first.
	UpdateEventStructs(event);

	// Exit program on esc push.
	if (keyboard.escape)
		running = false;

	// User movement
	if ((!keyboard.w && !keyboard.s) || (keyboard.w && keyboard.s))
		testPlayer->yVel = 0;
	else if (keyboard.w)
		testPlayer->yVel = -1;
	else if (keyboard.s)
		testPlayer->yVel = 1;

	if ((!keyboard.a && !keyboard.d) || (keyboard.a && keyboard.d))
		testPlayer->xVel = 0;
	else if (keyboard.a)
		testPlayer->xVel = -1;
	else if (keyboard.d)
		testPlayer->xVel = 1;

	// Sprint dodge etc...
	if (keyboard.lShift)
	{
		if (testPlayer->dodgesLeft > 0)
		{
			testPlayer->currentMovementVel = testPlayer->dodgeVel;
			testPlayer->dodgesLeft--;
		}

		keyboard.lShift = false;
	}

	SDL_Point facing = GetMapCoordFromCursor();

	testPlayer->directionFacing.x = static_cast <float> (facing.x);
	testPlayer->directionFacing.y = static_cast <float> (facing.y);

	testPlayer->MovePlayerAccordingToInput();


	// Fire weapon if needed.
	if (mouse.left)
	{		
		if (testPlayer->weapon.size() > 0)
		{
			testPlayer->FireWeapon();
			if (testPlayer->weapon[testPlayer->selectedWeapon]->fireType == FireType::SemiAuto)
			{
				mouse.left = false;
				testPlayer->isFiring = false;
			}
			else
				testPlayer->isFiring = true;
		}
	}
	else	
		testPlayer->isFiring = false;

	// Draw/place land.
	if (mouse.right)
	{
		SDL_Point mapPoint = GetMapCoordFromCursor();

		for (int x = mapPoint.x - 2; x <= mapPoint.x + 2; x++)
			for (int y = mapPoint.y - 2; y <= mapPoint.y + 2; y++)	
				map.SetDataAt(x, y, MapDataType::Wall, baseWallHealth);		
	}

	// Change weapons on roller ball.
	if (mouse.scrollUp)
	{
		testPlayer->SwitchToNextWeapon();
		mouse.scrollUp = false;
	}

	if (mouse.scrollDown)
	{
		testPlayer->SwitchToLastWeapon();
		mouse.scrollDown = false;
	}	

	// If player hits reload then reload weapon.
	if (keyboard.r)
		testPlayer->ReloadWeapon();

	// calculate all physics for all currently existing projectiles.
	allProjectiles.CalcAllProjectiles();

	// handle all player based events (reloading, recoil etc...)
	allPlayers.HandlePlayerEvents();
}