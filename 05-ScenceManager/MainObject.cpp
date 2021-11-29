#include "MainObject.h"
#include "Textures.h"
#include "Utils.h"
#include "Game.h"
#include "Brick.h"

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
{	// Calculate dx, dy 

	dx = dy = 0;

	float x0 = x, y0 = y;

	CGameObject::Update(dt);

	// Simple fall down
	//vy += MARIO_GRAVITY * dt;

	if (coObjects != NULL) {

		vector<LPGAMEOBJECT>* return_list = new vector<LPGAMEOBJECT>();

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		if (GetTickCount() - untouchable_start > MAINOBJECT_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		coEvents.clear();

		if (state != MAINOBJECT_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);

		int count = 0;

		for (int i = 0; i < coEvents.size(); i++)
			if (coEvents[i]->t > 0)
				count++;

		if (count == 0)
		{
			x0 += dx;
			y0 += dy;
			yWorld = 495 - y - MAINOBJECT_HEIGHT;
		}
		else {
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			x0 += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y0 += min_ty * dy + ny * 0.4f;

			if (ny == -1) {
				this->count = 0;
			}

			if (nx != 0)
				vx = 0;
			if (ny != 0) vy = 0;
		}

		for (UINT i = 0; i < coEvents.size(); i++) {
			LPCOLLISIONEVENT e = coEvents[i];
			//if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			//{
			CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				float a, b;
				if (e->obj)
					e->obj->GetRealPosition(a, b);
				DebugOut(L"Collide at mainX: %d, mainY: %d, brickX: %d, brickY: %d \n", int(this->x), int(this->yWorld), int(a), int(b));
			/*};*/
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			x = x0;
			y = y0;
		}
	}
}

bool check(Rect r, int vx, int vy, Rect obj, int& nx, int& ny, int dt) {
	Rect lr = r + Point(vx, vy) * dt;
	if (lr.IsCollide(obj)) {
		if (vx > 0)
			nx = obj.tf.x - lr.br.x;
		if (vy >= 0)
			ny = obj.tf.y - lr.br.y;
		return true;
	}
	return false;
}

void CMainObject::Render()
{
	float xRender, yRender;
	GetRealPosition(xRender, yRender);
	int ani = 0;
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
	int alpha = 255;
	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(xRender, yRender, alpha);
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
		ny = 0;
		WheelLeft->SetState(WHEEL_STATE_WALKING_RIGHT);
		WheelRight->SetState(WHEEL_STATE_WALKING_RIGHT);
		MainGun->SetState(GUN_STATE_RIGHT);
		break;
	case MAINOBJECT_STATE_WALKING_LEFT:
		vx = -MAINOBJECT_WALKING_SPEED;
		nx = -1;
		ny = 0;
		WheelLeft->SetState(WHEEL_STATE_WALKING_LEFT);
		WheelRight->SetState(WHEEL_STATE_WALKING_LEFT);
		MainGun->SetState(GUN_STATE_LEFT);
		break;
	case MAINOBJECT_STATE_JUMP:
		vy = MAINOBJECT_JUMP_SPEED_Y;
		nx = 0;
		ny = 1;
		break;
	case MAINOBJECT_STATE_IDLE:
		vx = 0;
		WheelLeft->SetState(WHEEL_STATE_IDLE);
		WheelRight->SetState(WHEEL_STATE_IDLE);
		break;

	case MAINOBJECT_STATE_DOWN:
		vy = -MAINOBJECT_JUMP_SPEED_Y;
		ny = -1;
		nx = 0;
		break;
	case MAINOBJECT_STATE_STOP:
		vy = vx = 0;
		//ny = 1;
		//nx = 0;
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
	return Rect(Point(x, y+6), MAINOBJECT_WIDTH - 1, MAINOBJECT_HEIGHT - 1);
}

void CMainObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 25;
	b = y + 25;
}

void CMainObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, yWorld, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;
	CGame::GetInstance()->Draw(x-5, yWorld, bbox, rect.left, rect.top, rect.right, rect.bottom, 80);
}
void CMainObject::Reset()
{
	vx = vy = 0;
}
