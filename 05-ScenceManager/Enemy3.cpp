#include "Enemy3.h"
#include "Utils.h"
Enemy3::Enemy3()
{
	SetState(ENEMY3_STATE_WALKING);
}

void Enemy3::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY3_BBOX_WIDTH;
	bottom = y + ENEMY3_BBOX_HEIGHT;
}

void Enemy3::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y = 350-20*sin(3*x);

	if (x0 == 0)
		x0 = x;
	if (vx < 0 && x < x0 - 50) {
		x = x0 - 50; vx = -vx;
	}

	if (vx > 0 && x > x0 + 50) {
		x = x0 + 50; vx = -vx;
	}
}

void Enemy3::Render()
{
	int ani = get_hit;
	if (state ==STATE_DIE) {
		return;
	}
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy3::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY3_STATE_WALKING:
		vx = -ENEMY3_WALKING_SPEED;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}