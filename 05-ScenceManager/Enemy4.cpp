#include "Enemy4.h"
Enemy4::Enemy4()
{
	SetState(ENEMY4_STATE_WALKING);
}

void Enemy4::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY4_BBOX_WIDTH;
	bottom = y + ENEMY4_BBOX_HEIGHT;
}

void Enemy4::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void Enemy4::Render()
{
	int ani = ENEMY4_ANI_WALKING;
	if (state == ENEMY4_STATE_DIE) {
		//ani = ENEMY4_ANI_DIE;
	}
	else
	animation_set->at(ani)->Render(x, y);

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