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
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
Rect CBrick::GetBoundingBox()
{
	return Rect(Point(x, y + 6), BRICK_BBOX_WIDTH - 1, BRICK_BBOX_HEIGHT - 1);
}


void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
{
	dx = dy = 0;

	if (x >= maxx || x <= minx) {
		vx *= -1;
	}
	if (y >= maxy || y <= miny)
		vy *= -1;

	CGameObject::Update(dt, coObjects);
}