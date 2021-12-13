#include "Portal.h"
#include "Utils.h"

CPortal::CPortal(float l, float t, float r, float b, int scene_id)
{
	type = 100;
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
}

void CPortal::Render()
{
	//animation_set->at(0)->Render(x, y, 255);
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}