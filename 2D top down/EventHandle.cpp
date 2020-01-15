#include "EventHandle.h"

#include "Globals.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Entity.h"

#include "Math functions.h"

#include <SDL.h>

// Handles all key/mouse events.
void UpdateEventStructs(SDL_Event event)
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				keyboard.a = true;
				break;

			case SDLK_b:
				keyboard.b = true;
				break;

			case SDLK_c:
				keyboard.c = true;
				break;

			case SDLK_d:
				keyboard.d = true;
				break;

			case SDLK_e:
				keyboard.e = true;
				break;

			case SDLK_f:
				keyboard.f = true;
				break;

			case SDLK_g:
				keyboard.g = true;
				break;

			case SDLK_h:
				keyboard.h = true;
				break;

			case SDLK_i:
				keyboard.i = true;
				break;

			case SDLK_j:
				keyboard.j = true;
				break;

			case SDLK_k:
				keyboard.k = true;
				break;

			case SDLK_l:
				keyboard.l = true;
				break;

			case SDLK_m:
				keyboard.m = true;
				break;

			case SDLK_n:
				keyboard.n = true;
				break;

			case SDLK_o:
				keyboard.o = true;
				break;

			case SDLK_p:
				keyboard.p = true;
				break;

			case SDLK_q:
				keyboard.q = true;
				break;

			case SDLK_r:
				keyboard.r = true;
				break;

			case SDLK_s:
				keyboard.s = true;
				break;

			case SDLK_t:
				keyboard.t = true;
				break;

			case SDLK_u:
				keyboard.u = true;
				break;

			case SDLK_v:
				keyboard.v = true;
				break;

			case SDLK_w:
				keyboard.w = true;
				break;

			case SDLK_x:
				keyboard.x = true;
				break;

			case SDLK_y:
				keyboard.y = true;
				break;

			case SDLK_z:
				keyboard.z = true;
				break;

			case SDLK_1:
				keyboard.n1 = true;
				break;

			case SDLK_2:
				keyboard.n2 = true;
				break;

			case SDLK_3:
				keyboard.n3 = true;
				break;

			case SDLK_4:
				keyboard.n4 = true;
				break;

			case SDLK_5:
				keyboard.n5 = true;
				break;

			case SDLK_6:
				keyboard.n6 = true;
				break;

			case SDLK_7:
				keyboard.n7 = true;
				break;

			case SDLK_8:
				keyboard.n8 = true;
				break;

			case SDLK_9:
				keyboard.n9 = true;
				break;

			case SDLK_0:
				keyboard.n0 = true;
				break;

			case SDLK_MINUS:
				keyboard.minus = true;
				break;

			case SDLK_PLUS:
				keyboard.plus = true;
				break;

			case SDLK_LEFTBRACKET:
				keyboard.leftBracket = true;
				break;

			case SDLK_RIGHTBRACKET:
				keyboard.rightBracket = true;
				break;

			case SDLK_LSHIFT:
				keyboard.lShift = true;
				break;

			case SDLK_RSHIFT:
				keyboard.rShift = true;
				break;

			case SDLK_LCTRL:
				keyboard.lCtrl = true;
				break;

			case SDLK_RCTRL:
				keyboard.rCtrl = true;
				break;

			case SDLK_LALT:
				keyboard.lAlt = true;
				break;

			case SDLK_RALT:
				keyboard.rAlt = true;
				break;

			case SDLK_ESCAPE:
				keyboard.escape = true;
				break;

			case SDLK_SPACE:
				keyboard.space = true;
				break;

			case SDLK_TAB:
				keyboard.tab = true;
				break;

			case SDLK_CAPSLOCK:
				keyboard.capsLock = true;
				break;
			}

			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				keyboard.a = false;
				break;

			case SDLK_b:
				keyboard.b = false;
				break;

			case SDLK_c:
				keyboard.c = false;
				break;

			case SDLK_d:
				keyboard.d = false;
				break;

			case SDLK_e:
				keyboard.e = false;
				break;

			case SDLK_f:
				keyboard.f = false;
				break;

			case SDLK_g:
				keyboard.g = false;
				break;

			case SDLK_h:
				keyboard.h = false;
				break;

			case SDLK_i:
				keyboard.i = false;
				break;

			case SDLK_j:
				keyboard.j = false;
				break;

			case SDLK_k:
				keyboard.k = false;
				break;

			case SDLK_l:
				keyboard.l = false;
				break;

			case SDLK_m:
				keyboard.m = false;
				break;

			case SDLK_n:
				keyboard.n = false;
				break;

			case SDLK_o:
				keyboard.o = false;
				break;

			case SDLK_p:
				keyboard.p = false;
				break;

			case SDLK_q:
				keyboard.q = false;
				break;

			case SDLK_r:
				keyboard.r = false;
				break;

			case SDLK_s:
				keyboard.s = false;
				break;

			case SDLK_t:
				keyboard.t = false;
				break;

			case SDLK_u:
				keyboard.u = false;
				break;

			case SDLK_v:
				keyboard.v = false;
				break;

			case SDLK_w:
				keyboard.w = false;
				break;

			case SDLK_x:
				keyboard.x = false;
				break;

			case SDLK_y:
				keyboard.y = false;
				break;

			case SDLK_z:
				keyboard.z = false;
				break;

			case SDLK_1:
				keyboard.n1 = false;
				break;

			case SDLK_2:
				keyboard.n2 = false;
				break;

			case SDLK_3:
				keyboard.n3 = false;
				break;

			case SDLK_4:
				keyboard.n4 = false;
				break;

			case SDLK_5:
				keyboard.n5 = false;
				break;

			case SDLK_6:
				keyboard.n6 = false;
				break;

			case SDLK_7:
				keyboard.n7 = false;
				break;

			case SDLK_8:
				keyboard.n8 = false;
				break;

			case SDLK_9:
				keyboard.n9 = false;
				break;

			case SDLK_0:
				keyboard.n0 = false;
				break;			

			case SDLK_MINUS:
				keyboard.minus = false;
				break;

			case SDLK_PLUS:
				keyboard.plus = false;
				break;

			case SDLK_LEFTBRACKET:
				keyboard.leftBracket = false;
				break;

			case SDLK_RIGHTBRACKET:
				keyboard.rightBracket = false;
				break;

			case SDLK_LSHIFT:
				keyboard.lShift = false;
				break;

			case SDLK_RSHIFT:
				keyboard.rShift = false;
				break;

			case SDLK_LCTRL:
				keyboard.lCtrl = false;
				break;

			case SDLK_RCTRL:
				keyboard.rCtrl = false;
				break;

			case SDLK_LALT:
				keyboard.lAlt = false;
				break;

			case SDLK_RALT:
				keyboard.rAlt = false;
				break;

			case SDLK_ESCAPE:
				keyboard.escape = false;
				break;

			case SDLK_SPACE:
				keyboard.space = false;
				break;

			case SDLK_TAB:
				keyboard.tab = false;
				break;

			case SDLK_CAPSLOCK:
				keyboard.capsLock = false;
				break;
			}
			break;

			// On mouse movement.
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouse.x, &mouse.y);
			break;

			// On mouse button down.
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse.left = true;
				break;

			case SDL_BUTTON_MIDDLE:
				mouse.middle = true;
				break;

			case SDL_BUTTON_RIGHT:
				mouse.right = true;
				break;
			}
			break;

			// On mouse button up.
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse.left = false;
				break;

			case SDL_BUTTON_MIDDLE:
				mouse.middle = false;
				break;

			case SDL_BUTTON_RIGHT:
				mouse.right = false;
				break;
			}
			break;
		}
	}
}
// Handles all keyboard/mouse events.
void EventHandle(SDL_Event& event)
{
	// Update all our structures handling what buttons are held down currently first.
	UpdateEventStructs(event);

	pl.dir = GetAngleAsDegrees(pl.point.x, pl.point.y, mouse.x, mouse.y);

	if (keyboard.escape)
		running = false;

	if (keyboard.w)
	{
		pl.point.y--;
		if (pl.point.y < 0)
			pl.point.y = 0;
	}

	if (keyboard.s)
	{
		pl.point.y++;
		if (pl.point.y > windowHeight - 1)
			pl.point.y = windowHeight - 1;
	}

	if (keyboard.a)
	{
		pl.point.x--;
		if (pl.point.x < 0)
			pl.point.x = 0;
	}

	if (keyboard.d)
	{
		pl.point.x++;
		if (pl.point.x > windowWidth - 1)
			pl.point.x = windowWidth - 1;
	}
}