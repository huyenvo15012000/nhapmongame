#include "Enemy1.h"
#include "Utils.h"
Enemy1::Enemy1()
{
}

void Enemy1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY1_BBOX_WIDTH;
	bottom = y + ENEMY1_BBOX_HEIGHT;
}

void Enemy1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void Enemy1::Render()
{
	int ani = ENEMY1_ANI_IDLE;
	if (state == ENEMY1_STATE_ITEM) {
		ani = ENEMY1_ANI_ITEM;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy1::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY1_STATE_DIE:
		vx = 0;
		vy = 0;
		DebugOut(L"Enemy1 die");
		break;
	}
}