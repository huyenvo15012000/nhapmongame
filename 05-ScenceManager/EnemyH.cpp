#include "EnemyH.h"
#include "Utils.h"
EnemyH::EnemyH()
{
	state = ENEMYH_STATE_IDLE;
}

void EnemyH::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMYH_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMYH_BBOX_WIDTH;
	bottom = y + ENEMYH_BBOX_HEIGHT;
}

void EnemyH::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void EnemyH::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMYH_ANI_IDLE;
	if (state == ENEMYH_STATE_ITEM) {
		ani = ENEMYH_ANI_ITEM;
	}
	if (state == ENEMYH_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void EnemyH::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMYH_STATE_DIE:
		DebugOut(L"EnemyH die");
		break;
	}
}