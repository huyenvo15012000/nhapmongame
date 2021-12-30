#include "SmallJason.h"
#include "Textures.h"
#include "Utils.h"
#include "Brick.h"
#include "Brick2.h"
#include "Brick3.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "PenetrableBrick.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Portal.h"
#include "Game.h"
#include "WallEnemy.h"
#include "MainObject.h"

#define ID_TEX_JASON_RIGHT			10
#define ID_TEX_JASON_LEFT 			11
SmallJason::SmallJason(float x, float y) : CGameObject()
{
	SetState(JASON_STATE_JUMP);
	this->x = x;
	this->y = y;
}

SmallJason::SmallJason() {

}
void SmallJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	vy = JASON_GRAVITY * dt;
	DebugOut(L"V: %f", x);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += vy;
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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		SetState(JASON_STATE_WALKING);
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			try {
				if (dynamic_cast<CPortal*>(e->obj))
				{
					CPortal* p = dynamic_cast<CPortal*>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
				}	
				if (dynamic_cast<CMainObject*>(e->obj))
				{
					x += dx;
					y += vy;
				}
			}
			catch (exception e) {

			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"X: %d, Y: %d \n", int(x), int(y));
}

void SmallJason::Render()
{
	int ani;
	int alpha = 255;	
	switch (state)
	{
	case JASON_STATE_JUMP:
		ani = JASON_ANI_JUMP;
		break;
	case JASON_STATE_WALKING:
		ani = JASON_ANI_WALK;		
	default:
		break;
	}
	animation_set->at(ani)->Render(x, y, alpha);
	RenderBoundingBox();
}

void SmallJason::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case JASON_STATE_WALKING:
		vx = JASON_WALKING_SPEED;
		break;
	case JASON_STATE_JUMP:
		
		break;
	
	}

}

SmallJason::~SmallJason()
{
}
void SmallJason::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x + 10;
	t = y - 13;
	r = x + JASON_BBOX_WIDTH + 6;
	b = y + JASON_BBOX_HEIGHT - 10;
}
void SmallJason::Reset()
{
	SetState(JASON_STATE_JUMP);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
