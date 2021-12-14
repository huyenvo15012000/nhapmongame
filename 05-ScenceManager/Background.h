#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  8
#define BRICK_BBOX_HEIGHT 8
#define OBJECT_TYPE_BACKGROUND	20


class Background : public CGameObject
{
public:
	Background()
	{
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

