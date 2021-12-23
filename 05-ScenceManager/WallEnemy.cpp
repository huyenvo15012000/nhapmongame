#include "WallEnemy.h"
#include "Utils.h"
WallEnemy::WallEnemy()
{
	state = WALLENEMY_STATE_IDLE;
}

void WallEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state ==STATE_DIE)
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
	DebugOut(L"State ene: %d %d %d \n", state, get_hit, animation_set->size());
	int ani = get_hit;
	if (state == STATE_DIE)
		animation_set->at(1)->Render(x, y);
	else
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