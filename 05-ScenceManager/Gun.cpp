#include "Gun.h"
#include "Textures.h"
#include "Utils.h"
#include "Brick.h"
#define ID_TEX_GUN_RIGHT			30
#define ID_TEX_GUN_LEFT 			31

void Gun::Update(DWORD dt)
{
	//CGameObject::Update(dt);

	//// Calculate dx, dy 
	//CGameObject::Update(dt);

	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();
	//if (GetTickCount64() - untouchable_start > GUN_UNTOUCHABLE_TIME)
	//{
	//	untouchable_start = 0;
	//	untouchable = 0;
	//}
	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{

	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
	//	//if (rdx != 0 && rdx!=dx)
	//	//	x += nx*abs(rdx); 

	//	// block every object first!
	//	x += min_tx * dx + nx * 0.4f;
	//	y += min_ty * dy + ny * 0.4f;

	//	if (nx != 0) vx = 0;
	//	if (ny != 0) vy = 0;
	//	//
	//	// Collision logic with other objects
	//	//
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];
	//		try {
	//			if (dynamic_cast<Enemy2*>(e->obj))
	//			{
	//				Enemy2* e2 = dynamic_cast<Enemy2*>(e->obj);
	//				e2->SetState(ENEMY2_STATE_DIE);
	//			}
	//			else if (dynamic_cast<CPortal*>(e->obj))
	//			{
	//				DebugOut(L"Okie \n");
	//				CPortal* p = dynamic_cast<CPortal*>(e->obj);
	//				CGame::GetInstance()->SwitchScene(p->GetSceneId());
	//			}
	//		}
	//		catch (exception e) {

	//		}
	//	}
}

void Gun::Render(float a, float b)
{
	int ani;
	switch (state) 
	{
	case GUN_STATE_RIGHT:
		ani = GUN_ANI_IDLE_RIGHT;
		break;
	case GUN_STATE_LEFT:
		ani = GUN_ANI_IDLE_LEFT;
		break;
	case GUN_STATE_UP:
		ani = GUN_ANI_IDLE_UP;
		break;
	}
	animation_set->at(ani)->Render(a, b, 255);
}

void Gun::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GUN_STATE_RIGHT:
		nx = 1;
		break;
	case GUN_STATE_LEFT:
		nx = -1;
		break;

	}


}


void Gun::Render()
{
	//animation_set->at(0)->Render(x, y,255);
	//RenderBoundingBox();
}

void Gun::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
