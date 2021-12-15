#include "Enemy4.h"
#include "Utils.h"
Enemy4::Enemy4()
{
	SetState(ENEMY4_STATE_WALKING);
}

void Enemy4::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != ENEMY4_STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY4_BBOX_WIDTH;
		bottom = y + ENEMY4_BBOX_HEIGHT;
	}
}

void Enemy4::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	if (x0 == 0)
		x0 = x;
	if (y0 == 0)
		y0 = y;
	x += dx;
	if (y0 < 200)
		y = 100 - 60 * sin(8 * x);
	else 
		y = 300 - 60 * sin(8*x);

	if (vx < 0 && x < x0-200) {
		x = x0 - 200; vx = -vx;
	}

	if (vx > 0 && x > x0+50) {
		x = x0+50; vx = -vx;
	}
}

void Enemy4::Render()
{
	int ani = ENEMY4_ANI_WALKING;
	switch (state)
	{
		case ENEMY4_STATE_ITEM:
			ani = ENEMY4_ANI_ITEM;
			break;
		case ENEMY4_STATE_DIE:
			ani = -1;
			break;
	}
	if (state == ENEMY4_STATE_DIE)
	{

	}
	else animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy4::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY4_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY4_STATE_WALKING:
		vx = -ENEMY4_WALKING_SPEED;
	}
}