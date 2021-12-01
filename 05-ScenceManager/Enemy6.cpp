#include "Enemy6.h"
Enemy6::Enemy6()
{
	SetState(ENEMY6_STATE_WALKING);
}

void Enemy6::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY6_BBOX_WIDTH;
	bottom = y + ENEMY6_BBOX_HEIGHT;
}

void Enemy6::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void Enemy6::Render()
{
	int ani = ENEMY6_ANI_WALKING;
	if (state == ENEMY6_STATE_DIE) {
		ani = ENEMY6_ANI_DIE;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy6::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY6_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY6_STATE_WALKING:
		vx = -ENEMY6_WALKING_SPEED;
	}
}