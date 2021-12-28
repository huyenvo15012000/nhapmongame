#include "WallEnemy.h"
#include "Utils.h"
WallEnemy::WallEnemy()
{
	state = WALLENEMY_STATE_IDLE;
}

void WallEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
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
	int ani = get_hit;
	if (get_hit>=1)
		animation_set->at(1)->Render(x, y);
	else
		animation_set->at(0)->Render(x, y);
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