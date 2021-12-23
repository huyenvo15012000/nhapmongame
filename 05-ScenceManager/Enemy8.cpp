#include "Enemy8.h"
#include "Utils.h"
Enemy8::Enemy8()
{
	SetState(ENEMY8_STATE_WALKING);
}

void Enemy8::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
		return;
	left = x;
	top = y;
	right = x + ENEMY8_BBOX_WIDTH;
	bottom = y + ENEMY8_BBOX_HEIGHT;
}

void Enemy8::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;
	if (x0 == 0)
		x0 = x;
	if (y0 == 0)
		y0 = y;
	if (vx < 0 && x < x0 - 30)
		vx = -vx;
	if (vx > 0 && x > x0 + 30)
		vx = -vx;
	if (vy < 0 && y < y0 - 20)
		vy = -vy;
	if (vy > 0 && y > y0 + 20)
		vy = -vy;
}

void Enemy8::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE) {
		return;
	}
	else
		animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy8::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY8_STATE_WALKING:
		vx = ENEMY8_WALKING_SPEED;
		vy = -ENEMY8_WALKING_SPEED;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}