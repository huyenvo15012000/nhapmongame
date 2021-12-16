#include "EnemyZiczacX.h"
#include "Utils.h"
EnemyZiczacX::EnemyZiczacX()
{
	state = ENEMYZICZACX_STATE_IDLE;
}

void EnemyZiczacX::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMYZICZACX_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMYZICZACX_BBOX_WIDTH;
	bottom = y + ENEMYZICZACX_BBOX_HEIGHT;
}

void EnemyZiczacX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void EnemyZiczacX::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMYZICZACX_ANI_IDLE;
	if (state == ENEMYZICZACX_STATE_ITEM) {
		ani = ENEMYZICZACX_ANI_ITEM;
	}
	if (state == ENEMYZICZACX_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void EnemyZiczacX::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMYZICZACX_STATE_DIE:
		DebugOut(L"EnemyZiczacX die");
		break;
	}
}