#include "Connector.h"
#include "Utils.h"

#define ID_TEX_CONNECTOR		20

void Connector::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void Connector::Render()
{
	//animation_set->at(0)->Render(x, y, 255);
}

void Connector::Render(float a, float b)
{
	int alpha = 255;
	animation_set->at(0)->Render(a, b, alpha);

	//RenderBoundingBox();
}

void Connector::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//l = x;
	//t = y;
	/*r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;*/
}