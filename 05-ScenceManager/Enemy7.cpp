#include "Enemy7.h"
Enemy7::Enemy7()
{
	SetState(ENEMY7_STATE_WALKING);
}

void Enemy7::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
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

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void Enemy7::Render()
{
	int ani = ENEMY7_ANI_WALKING;
	if (state == ENEMY7_STATE_DIE) {
		ani = ENEMY7_ANI_DIE;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy7::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY7_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY7_STATE_WALKING:
		vx = -ENEMY7_WALKING_SPEED;
	}
}