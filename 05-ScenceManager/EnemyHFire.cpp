#include "EnemyHFire.h"
#include "Utils.h"
#include "Brick2.h"
#include "PenetrableBrick.h"
EnemyHFire::EnemyHFire()
{
	state = ENEMYHFIRE_STATE_IDLE;
}

void EnemyHFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMYHFIRE_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMYHFIRE_BBOX_WIDTH;
	bottom = y + ENEMYHFIRE_BBOX_HEIGHT;
}

void EnemyHFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void EnemyHFire::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMYHFIRE_ANI_IDLE;
	if (state == ENEMYHFIRE_STATE_ITEM) {
		ani = ENEMYHFIRE_ANI_ITEM;
	}
	if (state == ENEMYHFIRE_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void EnemyHFire::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMYHFIRE_STATE_DIE:
		DebugOut(L"EnemyHFire die");
		break;
	}
}