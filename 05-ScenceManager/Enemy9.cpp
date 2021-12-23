#include "Enemy9.h"
#include "Utils.h"

Enemy9::Enemy9()
{
	SetState(ENEMY9_STATE_WALKING);
}

void Enemy9::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
		return;
	left = x;
	top = y;
	right = x + ENEMY9_BBOX_WIDTH;
	bottom = y + ENEMY9_BBOX_HEIGHT;
}

void Enemy9::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	if (x0 == 0)
		x0 = x;
	x += dx;

	if (vx < 0 && x < x0 - 70) {
		x = x0 - 70; vx = -vx;
	}

	if (vx > 0 && x > x0 + 70) {
		x = x0 + 70; vx = -vx;
	}
}

void Enemy9::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE) {
		return;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy9::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY9_STATE_WALKING:
		vx = ENEMY9_WALKING_SPEED;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}