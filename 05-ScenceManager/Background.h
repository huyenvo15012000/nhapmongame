#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  8
#define BRICK_BBOX_HEIGHT 8

class Background : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

