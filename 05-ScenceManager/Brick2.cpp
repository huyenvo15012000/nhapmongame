#include "Brick2.h"
#include "Rect.h"
#include "Utils.h"

void Brick2::Render()
{
	//animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void Brick2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x-2;
	t = y;
	r = x + BRICK_BBOX_WIDTH - 7;
	b = y + BRICK_BBOX_HEIGHT -3;
}