#include "WallEnemy.h"
#include "Utils.h"
WallEnemy::WallEnemy()
{
	state = WALLENEMY_STATE_IDLE;
}

void WallEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == WALLENEMY_STATE_DIE)
		return;
	left = x;
	top = y;
	right = x + WALLENEMY_BBOX_WIDTH;
	bottom = y + WALLENEMY_BBOX_HEIGHT;
}

void WallEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void WallEnemy::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = WALLENEMY_ANI_IDLE;
	if (state == WALLENEMY_STATE_DIE) {
		ani = WALLENEMY_ANI_ITEM;
		return;
	}
	RenderBoundingBox();
	animation_set->at(1)->Render(x, y);

}

void WallEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WALLENEMY_STATE_DIE:
		DebugOut(L"WallEnemy die");
		break;
	}
}