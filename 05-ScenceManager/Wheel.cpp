#include "Wheel.h"
#include "Textures.h"


#define ID_TEX_WHEEL_RIGHT			40
#define ID_TEX_WHEEL_LEFT 			41

void Wheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void Wheel::Render(float a, float b)
{
	int ani;
	if (vx == 0) ani = WHEEL_ANI_IDLE;
	else
		if (vx > 0)
			ani = WHEEL_ANI_WALKING_RIGHT;
		else
			ani = WHEEL_ANI_WALKING_LEFT;
	animation_set->at(ani)->Render(a, b);
}

void Wheel::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHEEL_STATE_WALKING_RIGHT:
		vx = WHEEL_WALKING_SPEED;
		nx = 1;
		break;
	case WHEEL_STATE_WALKING_LEFT:
		vx = -WHEEL_WALKING_SPEED;
		nx = -1;
		break;
	case WHEEL_STATE_JUMP:
		vy = -WHEEL_WALKING_SPEED;

	case WHEEL_STATE_IDLE:
		vx = 0;
		break;

	case WHEEL_STATE_DOWN:
		vy = WHEEL_WALKING_SPEED;
		break;
	}


}


void Wheel::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//l = x;
	//t = y;/*
	//r = x + BRICK_BBOX_WIDTH;
	//b = y + BRICK_BBOX_HEIGHT;*/
}
void Wheel::Render()
{
	//animation_set->at(0)->Render(x, y, 255);
}