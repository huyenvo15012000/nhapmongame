#include "Enemy10.h"
#include "Utils.h"
Enemy10::Enemy10()
{
	state = ENEMY10_STATE_WALKING;
}

void Enemy10::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY10_BBOX_WIDTH;
	bottom = y + ENEMY10_BBOX_HEIGHT;
}

void Enemy10::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void Enemy10::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMY10_ANI_WALKING;
	if (state == ENEMY10_STATE_DIE) {
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void Enemy10::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY10_STATE_DIE:
		DebugOut(L"Enemy10 die");
		break;
	}
}