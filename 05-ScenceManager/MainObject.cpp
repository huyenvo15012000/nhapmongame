#include "MainObject.h"
#include "Textures.h"
#include "Utils.h"
#include "Game.h"

#define ID_TEX_MAINOBJECT_RIGHT			10
#define ID_TEX_MAINOBJECT_LEFT 			11
#define BRICK_BBOX_WIDTH			8
#define BRICK_BBOX_HEIGHT 			8

CMainObject::CMainObject(float x, float y) : CGameObject()
{
	//SetState(MAINOBJECT_STATE_IDLE);
	untouchable = 0;
	this->x = x;
	this->y = y;
	this->yWorld = 496 - y - MAINOBJECT_HEIGHT;
}

CMainObject::CMainObject() {
	untouchable = 0;
	WheelLeft = new Wheel();
	WheelRight = new Wheel();
	this->MainGun = new Gun();
	connector = new Connector();
	this->x = x;
	this->y = y;
	this->yWorld = 496 - y - MAINOBJECT_HEIGHT;
}
void CMainObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	// simple fall down
	/*vy += MAINOBJECT_GRAVITY;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
	}*/

	//simple screen edge collision!!!
	//DebugOut(L"Main Update %d \n ", int(y));
	
	//this->y = 496 - this->y;
	//DebugOut(L"Y sau là : %d \n", int(this->y));
	if (vx > 0 && x > RIGHT_BORDER) x = RIGHT_BORDER;
	if (vx < 0 && x < LEFT_BORDER) x = LEFT_BORDER;
	if (vy < 0 && y < TOP_BORDER) y = TOP_BORDER;
	if (vy > 0 && y > BOTTOM_BORDER) y = BOTTOM_BORDER;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MAINOBJECT_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	/*if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		yWorld = 496 - y - MAINOBJECT_HEIGHT;
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

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			//if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			//{
			//	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

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
			}
		}
}

void CMainObject::Render()
{

	/*float z = 496 - int(y);
	if (z < 0)
		z *= -1;*/
	DebugOut(L"Main render");
	float xRender, yRender;
	GetRealPosition(xRender, yRender);
	int ani;
	if (nx > 0)
	{
		ani = MAINOBJECT_ANI_IDLE_RIGHT;
		MainGun->Render(xRender + 15, yRender);
	}
	else
		if (nx < 0)
		{
			ani = MAINOBJECT_ANI_IDLE_LEFT;
			MainGun->Render(xRender - 8, yRender);
		}
	RenderBoundingBox();
	animation_set->at(ani)->Render(xRender, yRender);
	WheelLeft->Render(xRender - 5, yRender + 12);
	WheelRight->Render(xRender + 11, yRender + 12);
	connector->Render(xRender + 3, yRender + 8);
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
		vy = MAINOBJECT_JUMP_SPEED_Y;
		break;
	case MAINOBJECT_STATE_IDLE:
		vx = 0;
		WheelLeft->SetState(WHEEL_STATE_IDLE);
		WheelRight->SetState(WHEEL_STATE_IDLE);
		break;

	case MAINOBJECT_STATE_DOWN:
		vy = -MAINOBJECT_JUMP_SPEED_Y;
		break;
	case MAINOBJECT_STATE_STOP:
		vy = vx = 0;
		WheelLeft->SetState(WHEEL_STATE_IDLE);
		WheelRight->SetState(WHEEL_STATE_IDLE);
		break;
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

Rect CMainObject::GetBoundingBox()
{
	DebugOut(L"Boud 1 \n");
	return Rect(Point(x, y+6), MAINOBJECT_WIDTH - 1, MAINOBJECT_HEIGHT - 1);
}

void CMainObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 30;
	b = y + 25;
}

void CMainObject::RenderBoundingBox()
{
	DebugOut(L"Main render bb");
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x-15, y+30, bbox, rect.left, rect.top, rect.right, rect.bottom, 80);
}

