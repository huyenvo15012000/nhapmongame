#pragma once
#include "GameObject.h"

#define BRICK2_BBOX_WIDTH  16
#define BRICK2_BBOX_HEIGHT 16


class Brick2 : public CGameObject
{

public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};