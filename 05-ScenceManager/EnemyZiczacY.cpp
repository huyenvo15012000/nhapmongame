#include "EnemyZiczacY.h"
#include "Utils.h"
EnemyZiczacY::EnemyZiczacY()
{
	state = ENEMYZICZACY_STATE_IDLE;
}

void EnemyZiczacY::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMYZICZACY_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMYZICZACY_BBOX_WIDTH;
	bottom = y + ENEMYZICZACY_BBOX_HEIGHT;
}

void EnemyZiczacY::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void EnemyZiczacY::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMYZICZACY_ANI_IDLE;
	if (state == ENEMYZICZACY_STATE_ITEM) {
		ani = ENEMYZICZACY_ANI_ITEM;
	}
	if (state == ENEMYZICZACY_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void EnemyZiczacY::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMYZICZACY_STATE_DIE:
		DebugOut(L"EnemyZiczacY die");
		break;
	}
}