#include "EnemyH.h"
#include "Utils.h"
#include "Brick2.h"
#include "PenetrableBrick.h"
EnemyH::EnemyH()
{
	state = ENEMYH_STATE_IDLE;
}

void EnemyH::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
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
	CGameObject::Update(dt);
	x += vx * dt;
	if (x < 30 && vx < 0)
	{
		x = 30;
		vx = -vx;
	}
	if (x > 200 && vx > 0)
	{
		x = 200;
		vx = -vx;
	}
}

void EnemyH::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = get_hit;
	if (state == STATE_DIE)
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
	case STATE_DIE:
		DebugOut(L"EnemyH die");
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}