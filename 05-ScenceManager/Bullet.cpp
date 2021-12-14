#include "Bullet.h"
#include "Utils.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Brick.h"

Bullet::Bullet(int nx, int ny)
{
	this->nyy = ny;
	this->nx = nx;
	if (nyy != 0)
		vy = nyy * 0.1f;
	else vx = nx * 0.1f;
}
void Bullet::Render()
{
	if (nyy != 0)
		animation_set->at(1)->Render(x, y+20);
	else
		animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}


void Bullet::GetBoundingBox(float& l, float& t, float& r, float& b)
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

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//dx = dy = 0;
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

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

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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
		this->SetState(BULLET_STATE_DIE);
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Enemy1*>(e->obj))
			{
				DebugOut(L"Enemy 1");
				Enemy1* e1 = dynamic_cast<Enemy1*>(e->obj);
				e1->SetState(ENEMY1_STATE_ITEM);
			}
			if (dynamic_cast<Enemy2*>(e->obj))
			{
				Enemy2* e2 = dynamic_cast<Enemy2*>(e->obj);
				e2->SetState(ENEMY2_STATE_DIE);
			}
			if (dynamic_cast<Enemy3*>(e->obj))
			{
				Enemy3* e3 = dynamic_cast<Enemy3*>(e->obj);
				e3->SetState(ENEMY3_STATE_DIE);
			}
			if (dynamic_cast<Enemy4*>(e->obj))
			{
				Enemy4* e4 = dynamic_cast<Enemy4*>(e->obj);
				e4->SetState(ENEMY4_STATE_DIE);
			}
			if (dynamic_cast<Enemy5*>(e->obj))
			{
				Enemy5* e5 = dynamic_cast<Enemy5*>(e->obj);
				e5->SetState(ENEMY5_STATE_DIE);
			}
			if (dynamic_cast<Enemy6*>(e->obj))
			{
				Enemy6* e6 = dynamic_cast<Enemy6*>(e->obj);
				e6->SetState(ENEMY6_STATE_DIE);
			}
			if (dynamic_cast<Enemy7*>(e->obj))
			{
				Enemy7* e7 = dynamic_cast<Enemy7*>(e->obj);
				e7->SetState(ENEMY3_STATE_DIE);
			}

			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (goomba->GetState() != GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -MARIO_JUMP_DEFLECT_SPEED;
			//		}
			//	}
			//	else if (e->nx != 0)
			//	{
			//		if (untouchable == 0)
			//		{
			//			if (goomba->GetState() != GOOMBA_STATE_DIE)
			//			{
			//				if (level > MARIO_LEVEL_SMALL)
			//				{
			//					level = MARIO_LEVEL_SMALL;
			//					StartUntouchable();
			//				}
			//				else
			//					SetState(MARIO_STATE_DIE);
			//			}
			//		}
			//	}
			//} // if Goomba
			//else if (dynamic_cast<CPortal*>(e->obj))
			//{
			//	CPortal* p = dynamic_cast<CPortal*>(e->obj);
			//	CGame::GetInstance()->SwitchScene(p->GetSceneId());
			//}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//y += 0.1;
}
void Bullet::SetState(int state)
{
	this->state = state;
}