#include "Enemy5.h"
Enemy5::Enemy5()
{
	SetState(ENEMY5_STATE_WALKING);
}

void Enemy5::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
		return;
	left = x;
	top = y;
	right = x + ENEMY5_BBOX_WIDTH;
	bottom = y + ENEMY5_BBOX_HEIGHT;
}

void Enemy5::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	/*x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}*/
}

void Enemy5::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE) {
		return;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy5::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY5_STATE_WALKING:
		vx = -ENEMY5_WALKING_SPEED;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}