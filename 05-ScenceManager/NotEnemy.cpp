#include "NotFireEnemy.h"
#include "Utils.h"
NotFireEnemy::NotFireEnemy()
{
	state = NOTFIREENEMY_STATE_IDLE;
}

void NotFireEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == NOTFIREENEMY_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + NOTFIREENEMY_BBOX_WIDTH;
	bottom = y + NOTFIREENEMY_BBOX_HEIGHT;
}

void NotFireEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void NotFireEnemy::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = NOTFIREENEMY_ANI_IDLE;
	if (state == NOTFIREENEMY_STATE_ITEM) {
		ani = NOTFIREENEMY_ANI_ITEM;
	}
	if (state == NOTFIREENEMY_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void NotFireEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case NOTFIREENEMY_STATE_DIE:
		DebugOut(L"NotFireEnemy die");
		break;
	}
}