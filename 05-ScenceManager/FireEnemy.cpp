#include "FireEnemy.h"
#include "Utils.h"

FireEnemy::FireEnemy()
{
	state = FIREENEMY_STATE_IDLE;
}

void FireEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FIREENEMY_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + FIREENEMY_BBOX_WIDTH;
	bottom = y + FIREENEMY_BBOX_HEIGHT;
}

void FireEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float player_x, player_y;
	coObjects->at(coObjects->size() - 1)->GetPosition(player_x, player_y);
	float distance = sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	if ( distance <= 200)
		MoveToPlayer(player_x, player_y);
	DebugOut(L"Move X: %d, Y: %d , D: %f \n", int(player_x), int(player_y), distance);
}

void FireEnemy::MoveToPlayer(float a, float b)
{
	DebugOut(L"Move X: %d, Y: %d \n", int(a), int(b));
	float u0 = a - x;
	float u1 = b - y;
	x += vx * u0;
	y += vy * u1;
}
void FireEnemy::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = FIREENEMY_ANI_IDLE;
	if (state == FIREENEMY_STATE_ITEM) {
		ani = FIREENEMY_ANI_ITEM;
	}
	if (state == FIREENEMY_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void FireEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREENEMY_STATE_DIE:
		DebugOut(L"FireEnemy die");
		break;
	}
}