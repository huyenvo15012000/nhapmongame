#include "MainObject.h"
#include "Textures.h"
#include "Utils.h"
#include "Brick.h"
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

#define ID_TEX_MAINOBJECT_RIGHT			10
#define ID_TEX_MAINOBJECT_LEFT 			11
int bullet_ny = 0;
int old_ani;
float bullet_x, bullet_y;
CMainObject::CMainObject(float x, float y) : CGameObject()
{
	SetState(MAINOBJECT_STATE_IDLE);
	this->x = x;
	this->y = y;
}

CMainObject::CMainObject() {
	WheelLeft = new Wheel();
	WheelRight = new Wheel();
	this->MainGun = new Gun();
	connector = new Connector();
	healthbar = new HealthBar();
	bullet = new Bullet(nx, bullet_ny,0);

}
void CMainObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin() + i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	// Simple fall down
	if (!IsJason())
		vy = MAINOBJECT_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MAINOBJECT_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MAINOBJECT_UNTOUCHABLE_TIME)
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
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			try {
				if (dynamic_cast<PenetrableBrick*>(e->obj))
				{
					x += dx;
					y += dy;
				}
				else if (dynamic_cast<Enemy1*>(e->obj))
				{
					Enemy1* e2 = dynamic_cast<Enemy1*>(e->obj);
					e2->SetState(ENEMY1_STATE_DIE);
					this->Hit();
				}
				else if (dynamic_cast<Enemy2*>(e->obj))
				{
					Enemy2* e2 = dynamic_cast<Enemy2*>(e->obj);
					this->Hit();
				}
				else if (dynamic_cast<CPortal*>(e->obj))
				{
					DebugOut(L"Okie \n");
					CPortal* p = dynamic_cast<CPortal*>(e->obj);
					CGame::GetInstance()->SwitchScene(p->GetSceneId());
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

void CMainObject::Render()
{
	int ani;
	DebugOut(L"Vx: %f, vy: %f", vx, vy);
	if (nx > 0)
	{
		ani = MAINOBJECT_ANI_WALKING_RIGHT;
		old_ani = ani;
		if (!IsJason())
		{
			ani = MAINOBJECT_ANI_IDLE_RIGHT;
			if (bullet_ny == 0)
			{
				MainGun->Render(x + 15, y);
				MainGun->SetState(GUN_STATE_RIGHT);	
				WheelLeft->Render(x, y - 8);
				WheelRight->Render(x + 14, y - 8);
				connector->Render(x + 8, y - 8);
				animation_set->at(MAINOBJECT_ANI_IDLE_RIGHT)->Render(x, y, 255);
				bullet_x = x + 12;
				bullet_y = y;
			}
			else
			{
				MainGun->SetState(GUN_STATE_UP);
				MainGun->Render(x+7, y + 17);
				WheelLeft->Render(x+3, y - 8);
				WheelRight->Render(x + 13, y - 8);
				connector->Render(x + 8, y - 1);
				animation_set->at(MAINOBJECT_ANI_FIRE_UP_RIGHT)->Render(x, y+10, 255);
				bullet_x = x + 7;
				bullet_y = y+17;
			}
		}
	}
	else
		if (nx < 0)
		{
			ani = MAINOBJECT_ANI_WALKING_LEFT;
			old_ani = ani;
			if (!IsJason())
			{
				if (bullet_ny == 0)
				{
					ani = MAINOBJECT_ANI_IDLE_LEFT;
					MainGun->Render(x - 8, y);
					MainGun->SetState(GUN_STATE_LEFT);
					WheelLeft->Render(x - 4, y - 8);
					WheelRight->Render(x + 9, y - 8);
					connector->Render(x + 2, y - 8);
					animation_set->at(MAINOBJECT_ANI_IDLE_LEFT)->Render(x, y, 255);
					bullet_x = x-8;
					bullet_y = y;
				}
				else
				{
					MainGun->SetState(GUN_STATE_UP);
					MainGun->Render(x, y + 13);
					WheelLeft->Render(x -4, y - 8);
					WheelRight->Render(x + 6, y - 8);
					connector->Render(x , y - 2);
					animation_set->at(MAINOBJECT_ANI_FIRE_UP_LEFT)->Render(x, y+8, 255);
					bullet_x = x+3;
					bullet_y = y+13;
				}
			}
		}
	int alpha = 255;
	if (untouchable) alpha = 128;
	if (nyy > 0)
		ani = JASON_ANI_BACK;
	if (nyy < 0)
		ani = JASON_ANI_IDLE;
	if (IsJason())
		animation_set->at(ani)->Render(x, y, alpha);

	for (int i = 0; i < bullets.size();i++)
		bullets[i]->Render();
	if (x-160<0)
		healthbar->Render(0, y, get_hit);
	else healthbar->Render(x - 160, y, get_hit);
	RenderBoundingBox();
}

void CMainObject::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MAINOBJECT_STATE_WALKING_RIGHT:
		vx = MAINOBJECT_WALKING_SPEED;
		if (IsJason())
			vy = 0;
		nx = 1;
		nyy = 0;
		if (WheelLeft != NULL && WheelRight != NULL && MainGun != NULL)
		{
			WheelLeft->SetState(WHEEL_STATE_WALKING_RIGHT);
			WheelRight->SetState(WHEEL_STATE_WALKING_RIGHT);
			MainGun->SetState(GUN_STATE_RIGHT);
		}
		break;
	case MAINOBJECT_STATE_WALKING_LEFT:
		vx = -MAINOBJECT_WALKING_SPEED;
		if (IsJason())
			vy = 0;
		nx = -1;
		nyy = 0;
		if (WheelLeft != NULL && WheelRight != NULL && MainGun != NULL)
		{
			MainGun->SetState(GUN_STATE_LEFT);
			WheelLeft->SetState(WHEEL_STATE_WALKING_LEFT);
			WheelRight->SetState(WHEEL_STATE_WALKING_LEFT);
		}
		break;
	case MAINOBJECT_STATE_WALKING_UP:
		vy = MAINOBJECT_WALKING_SPEED;
		vx = 0;
		nx = 0;
		nyy = 1;
		if (WheelLeft != NULL && WheelRight != NULL && MainGun != NULL)
		{
			WheelLeft->SetState(WHEEL_STATE_WALKING_RIGHT);
			WheelRight->SetState(WHEEL_STATE_WALKING_RIGHT);
			MainGun->SetState(GUN_STATE_RIGHT);
		}
		break;
	case MAINOBJECT_STATE_WALKING_DOWN:
		vy = -MAINOBJECT_WALKING_SPEED;
		vx = 0;
		nyy = -1;
		nx = 0;
		if (WheelLeft != NULL && WheelRight != NULL && MainGun != NULL)
		{
			MainGun->SetState(GUN_STATE_LEFT);
			WheelLeft->SetState(WHEEL_STATE_WALKING_LEFT);
			WheelRight->SetState(WHEEL_STATE_WALKING_LEFT);
		}
		break;
	case MAINOBJECT_STATE_JUMP:
		//if (!IsCollide)
		vy = MAINOBJECT_JUMP_SPEED_Y;
		nyy = 1;
		break;
	case MAINOBJECT_STATE_IDLE:
		vx = 0;
		bullet_ny = 0;
		if (WheelLeft && WheelRight)
		{
			WheelLeft->SetState(WHEEL_STATE_IDLE);
			WheelRight->SetState(WHEEL_STATE_IDLE);
		}
		break;

	case MAINOBJECT_STATE_DOWN:
		vy = -MAINOBJECT_JUMP_SPEED_Y;
		break;
	case MAINOBJECT_STATE_FIRE:
		create_bullet_count = MAINOBJECT_AMOUNT_BULLET;
		this->Fire();
		break;
	case MAINOBJECT_STATE_STOP:
		if (IsJason())
		{
			vx = 0;
			vy = 0;
		}
		if (WheelLeft != NULL && WheelRight != NULL)
		{
			WheelLeft->SetState(WHEEL_STATE_IDLE);
			WheelRight->SetState(WHEEL_STATE_IDLE);
		}
		break;
	case MAINOBJECT_STATE_FIRE_UP:
		bullet_ny = 1;
	}

}

void CMainObject::addGun(Gun* gunf)
{
	MainGun = gunf;
}

void CMainObject::addConnector(Connector* connectorf)
{
	connector = connectorf;
}

void CMainObject::addWheel(Wheel* wheelF)
{
	WheelLeft = WheelRight = wheelF;
}
CMainObject::~CMainObject()
{
	delete WheelLeft;
	delete WheelRight;
	delete connector;
	delete MainGun;
}
void CMainObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 5;
	t = y - 11;
	if (!IsJason())
	{
		r = x + MAINOBJECT_BBOX_WIDTH - 5;
		b = y + MAINOBJECT_BBOX_HEIGHT - 11;
	}
	else
	{
		l = x + 10;
		t = y - 13;
		r = x + JASON_BBOX_WIDTH + 6;
		b = y + JASON_BBOX_HEIGHT - 10;
	}
}
void CMainObject::Reset()
{
	SetState(MAINOBJECT_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
void CMainObject::addBullet(Bullet* bulletF)
{
	bullet = bulletF;
	bullet->IsJason = IsJason();
}
void CMainObject::Fire()
{
	
	if (IsJason())
	{
		float va, vb;
		if (nyy > 0)
		{
			va = 1;
			vb = 1;
		}
		else
		{
			va = -1;
			vb = -1;
		}
		for (int i = 0; i < BULLET_NUMBER / 2; i++)
		{			
			Bullet* newBullet;
			newBullet = new Bullet(nx, nyy,0);
			newBullet->SetAnimationSet(bullet->animation_set);
			newBullet->SetPosition(x+va*i*10, y-i*vb*10);
			bullets.push_back(newBullet);
		}
		for (int i = 0; i < BULLET_NUMBER / 2; i++)
		{
			Bullet* newBullet;
			newBullet = new Bullet(nx, nyy,-1);
			newBullet->SetAnimationSet(bullet->animation_set);
			newBullet->SetPosition(x + va * i * 20, y - i * vb*20);
			bullets.push_back(newBullet);
		}
	}
	else {
		Bullet* newBullet;
		newBullet = new Bullet(nx, bullet_ny,0);
		newBullet->SetAnimationSet(bullet->animation_set);
		newBullet->SetPosition(bullet_x, bullet_y);
		bullets.push_back(newBullet);
	}
}