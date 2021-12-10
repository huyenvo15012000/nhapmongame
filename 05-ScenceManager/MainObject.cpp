#include "MainObject.h"
#include "Textures.h"
#include "Utils.h"
#include "Brick.h"
#include "Enemy2.h"

#define ID_TEX_MAINOBJECT_RIGHT			10
#define ID_TEX_MAINOBJECT_LEFT 			11
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
	bullet = new Bullet(nx, bullet_ny);

}
void CMainObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin()+i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	// Simple fall down
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
		IsCollide = false;
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
			if (dynamic_cast<Enemy2*>(e->obj))
				{
					Enemy2* e2 = dynamic_cast<Enemy2*>(e->obj);
					e2->SetState(ENEMY2_STATE_DIE);
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
}

void CMainObject::Render()
{
	int ani = 0;
	if (state == MAINOBJECT_STATE_FIRE_UP)
		if (nx > 0)
		{
			ani = MAINOBJECT_ANI_FIRE_UP_LEFT;
			MainGun->Render(x , y+5);
		}
		else
		{
			ani = MAINOBJECT_ANI_FIRE_UP_RIGHT;
			MainGun->Render(x, y + 5);
		}
	else if (nx > 0)
	{
		ani = MAINOBJECT_ANI_IDLE_RIGHT;
		MainGun->Render(x + 15, y);
	}
	else
		if (nx < 0)
		{
			ani = MAINOBJECT_ANI_IDLE_LEFT;
			MainGun->Render(x - 8, y);
		}
	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(2)->Render(x, y, alpha);
	WheelLeft->Render(x - 5, y - 12);
	WheelRight->Render(x + 11, y - 12);
	connector->Render(x + 3, y - 8);
	for (int i = 0; i < bullets.size();i++)
		bullets[i]->Render();
	RenderBoundingBox();
}

void CMainObject::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MAINOBJECT_STATE_WALKING_RIGHT:
		vx = MAINOBJECT_WALKING_SPEED;
		nx = 1;
		WheelLeft->SetState(WHEEL_STATE_WALKING_RIGHT);
		WheelRight->SetState(WHEEL_STATE_WALKING_RIGHT);
		MainGun->SetState(GUN_STATE_RIGHT);
		break;
	case MAINOBJECT_STATE_WALKING_LEFT:
		vx = -MAINOBJECT_WALKING_SPEED;
		nx = -1;
		WheelLeft->SetState(WHEEL_STATE_WALKING_LEFT);
		WheelRight->SetState(WHEEL_STATE_WALKING_LEFT);
		MainGun->SetState(GUN_STATE_LEFT);
		break;
	case MAINOBJECT_STATE_JUMP:
		//if (!IsCollide)
			vy = MAINOBJECT_JUMP_SPEED_Y;
		break;
	case MAINOBJECT_STATE_IDLE:
		vx = 0;
		vy = 0;
		if (WheelLeft && WheelRight)
		{
			WheelLeft->SetState(WHEEL_STATE_IDLE);
			WheelRight->SetState(WHEEL_STATE_IDLE);
		}
		break;

	case MAINOBJECT_STATE_DOWN:
		//if (!IsCollide)
			vy = -MAINOBJECT_JUMP_SPEED_Y;
		break;
	case MAINOBJECT_STATE_FIRE:
		//if (!IsCollide)
		create_bullet_count = MAINOBJECT_AMOUNT_BULLET;
		this->Fire();
		break;
	case MAINOBJECT_STATE_STOP:
		vy = vx = 0;
		WheelLeft->SetState(WHEEL_STATE_IDLE);
		WheelRight->SetState(WHEEL_STATE_IDLE);
		break;
	case MAINOBJECT_STATE_FIRE_UP:
		bullet_ny = 1;
		this->MainGun->SetState(GUN_ANI_IDLE_UP);
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
	l = x;
	t = y - 10;
	r = x + MAINOBJECT_BBOX_WIDTH - 1;
	b = y + MAINOBJECT_BBOX_HEIGHT - 11;
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
}
void CMainObject::Fire()
{
	for (int i = 0; i < MAINOBJECT_AMOUNT_BULLET;i++)
	{
		Bullet* newBullet = new Bullet(nx, bullet_ny);
		newBullet->SetAnimationSet(bullet->animation_set);
		if (bullets.size() == 0)
			if (nx>0)
				newBullet->SetPosition(x+10, y);
			else 
				newBullet->SetPosition(x - 10, y);
		else
		{
			float a, b;
			bullets[bullets.size() - 1]->GetPosition(a, b);
			newBullet->SetPosition(a-10, y);
		}
		bullets.push_back(newBullet);
	}
}