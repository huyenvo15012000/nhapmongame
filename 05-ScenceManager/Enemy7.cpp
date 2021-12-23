#include "Enemy7.h"
Enemy7::Enemy7()
{
	SetState(ENEMY7_STATE_WALKING);
}

void Enemy7::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
		return;
	left = x;
	top = y;
	right = x + ENEMY7_BBOX_WIDTH;
	bottom = y + ENEMY7_BBOX_HEIGHT;
}

void Enemy7::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

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

void Enemy7::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE) {
		return;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy7::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY7_STATE_WALKING:
		vx = -ENEMY7_WALKING_SPEED;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}