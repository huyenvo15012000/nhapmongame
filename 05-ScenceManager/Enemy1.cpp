#include "Enemy1.h"
#include "Utils.h"
Enemy1::Enemy1()
{
	state = ENEMY1_STATE_IDLE;
}

void Enemy1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
		return;
	left = x;
	top = y;
	right = x + ENEMY1_BBOX_WIDTH;
	bottom = y + ENEMY1_BBOX_HEIGHT;
}

void Enemy1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void Enemy1::Render()
{
	////DebugOut(L"State ene: %d \n", state);
	int ani = get_hit;
	if (state == STATE_DIE) {
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void Enemy1::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		DebugOut(L"Enemy1 die");
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}