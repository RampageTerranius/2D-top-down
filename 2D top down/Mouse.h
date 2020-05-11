#pragma once

struct Mouse
{
public:
	bool left, middle, right;
	int x, y;
	bool scrollUp, scrollDown, scrollLeft, scrollRight;
};

extern Mouse mouse;