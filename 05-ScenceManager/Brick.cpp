#include "Brick.h"
#include "Rect.h"

void CBrick::Render()
{
	animation_set->at(0)->Render(x, yWorld);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = yWorld;
	r = x + BRICK_BBOX_WIDTH;
	b = yWorld + BRICK_BBOX_HEIGHT;
}