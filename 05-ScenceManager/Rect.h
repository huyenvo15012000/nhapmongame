#pragma once
#include "Point.h"


class Rect
{
public:
	int x, y, width, height;
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	Rect(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
	}
};

