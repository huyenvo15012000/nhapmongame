#include "HealthBar.h"
#include "Utils.h"

void HealthBar::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void HealthBar::Render()
{
	//animation_set->at(0)->Render(x, y, 255);
}

void HealthBar::Render(float a, float b, int ani_id)
{
	int alpha = 255;
	if (ani_id<animation_set->size())
	animation_set->at(ani_id)->Render(a, b, alpha);

	//RenderBoundingBox();
}

void HealthBar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//l = x;
	//t = y;
	/*r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;*/
}