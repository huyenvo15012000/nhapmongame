#include "EnemyBullet.h"
#include "Utils.h"
#include "Brick.h"

EnemyBullet::EnemyBullet(int nx, int ny)
{
	this->nyy = ny;
	this->nx = nx;
	if (nyy != 0)
		vy = nyy * 0.1f;
	else vx = nx * 0.1f;
}
void EnemyBullet::Render()
{
	///*if (nyy != 0)
	//	animation_set->at(1)->Render(x - 5, y + 20);
	//else*/
	animation_set->at(0)->Render(x + nx * 5, y);
	RenderBoundingBox();
	DebugOut(L"EB x: %f, EB y: %f \n", x, y);
}


void EnemyBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (nyy != 0)
	{
		r = x + BULLET_WIDTH_U;
		b = y + BULLET_HEIGHT_U;
	}
	else
	{
		r = x + BULLET_WIDTH_H;
		b = y + BULLET_HEIGHT_H;
	}
}

void EnemyBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//dx = dy = 0;
	// Calculate dx, dy 
	CGameObject::Update(dt);
	float player_x, player_y;
	coObjects->at(coObjects->size() - 1)->GetPosition(player_x, player_y);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	float l, t, r, b;

	coEvents.clear();

	// turn off collision when die 
	if (state != BULLET_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > BULLET_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	//if (x>=player_x && x<=player_x+40 && y<=player_y && y>=)
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		//x += 0.1*dt;
		y += -0.09*dt;
		if (y < 0)
			this->SetState(BULLET_STATE_DIE);
	}/*
	if (y < 0)
		this->SetState(BULLET_STATE_DIE);*/
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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		this->SetState(BULLET_STATE_DIE);
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//y += 0.1;
}
void EnemyBullet::SetState(int state)
{
	this->state = state;
}