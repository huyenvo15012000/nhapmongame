#include "Gun.h"
#include "Textures.h"
#include "Utils.h"
#define ID_TEX_GUN_RIGHT			30
#define ID_TEX_GUN_LEFT 			31

void Gun::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL)
{
	CGameObject::Update(dt);
	x += GUN_WALKING_SPEED * dt;
	y += GUN_WALKING_SPEED * dt;
}

void Gun::Render(float a, float b)
{
	int ani;
	if (state == GUN_STATE_RIGHT) ani = GUN_ANI_IDLE_RIGHT;
	else ani = GUN_ANI_IDLE_LEFT;
	if (state == GUN_STATE_UP)
		ani = GUN_ANI_IDLE_UP;
	animation_set->at(ani)->Render(a, b, 255);
}

void Gun::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GUN_STATE_RIGHT:
		nx = 1;
		break;
	case GUN_STATE_LEFT:
		nx = -1;
		break;

	}


}


void Gun::Render()
{
	animation_set->at(0)->Render(x, y,255);
	//RenderBoundingBox();
}

void Gun::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
