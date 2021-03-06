#include "Brick.h"
#include "Rect.h"
#include "Utils.h"

void CBrick::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y-1;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}