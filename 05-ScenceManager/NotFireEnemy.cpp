#include "NotFireEnemy.h"
#include "Utils.h"
NotFireEnemy::NotFireEnemy()
{
	state = NOTFIREENEMY_STATE_IDLE;
}

void NotFireEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + NOTFIREENEMY_BBOX_WIDTH;
	bottom = y + NOTFIREENEMY_BBOX_HEIGHT;
}
void NotFireEnemy::MoveToPlayer(float a, float b)
{
	//DebugOut(L"Move X: %f, Y: %f \n", vx, vy);
	float u0 = a - x;
	float u1 = b - y;
	if (state == STATE_DIE)
		return;
	x += vx * u0;
	y += vy * u1;
}
void NotFireEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float player_x, player_y;
	coObjects->at(coObjects->size() - 1)->GetPosition(player_x, player_y);
	float distance = sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	//coObjects->pop_back();
	// turn off collision when die 
	if (state != NOTFIREENEMY_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		vx = vy = ENEMY_SPEED;
		if (distance <= 100 && state != STATE_ITEM)
			MoveToPlayer(player_x, player_y);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		/*vx = ENEMY_SPEED;
		vy = 0;*/
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		//
		// Collision logic with other objects
		//
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"X: %d, Y: %d \n", int(x), int(y));

}

void NotFireEnemy::Render()
{
	////DebugOut(L"State ene: %d \n", state);
	int ani = get_hit;
	//if (state == NOTFIREENEMY_STATE_ITEM) {
	//	ani = NOTFIREENEMY_ANI_ITEM;
	//}
	if (state == STATE_DIE)
		return;
	
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void NotFireEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = vy = 0;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}