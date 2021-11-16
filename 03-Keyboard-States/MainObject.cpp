#include "MainObject.h"
#include "debug.h"
#include "Textures.h"


#define ID_TEX_MAINOBJECT_RIGHT			10
#define ID_TEX_MAINOBJECT_LEFT 			11

CMainObject::CMainObject() {
	WheelLeft = new Wheel();
	WheelRight = new Wheel();
	this->MainGun = new Gun();
	connector = new Connector();

}
void CMainObject::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	/*vy += MAINOBJECT_GRAVITY;
	if (y > 100) 
	{
		vy = 0; y = 100.0f;
	}*/

	//simple screen edge collision!!!
	x += vx * dt;
	y += vy * dt;
	if (vx > 0 && x > RIGHT_BORDER ) x = RIGHT_BORDER;
	if (vx < 0 && x < LEFT_BORDER) x = LEFT_BORDER;
	if (vy < 0 && y < TOP_BORDER) y = TOP_BORDER;
	if (vy > 0 && y > BOTTOM_BORDER ) y = BOTTOM_BORDER;
}

void CMainObject::Render()
{
	int ani;
	if (nx>0) ani = MAINOBJECT_ANI_IDLE_RIGHT;
	else ani = MAINOBJECT_ANI_IDLE_LEFT;
	animations[ani]->Render(x, y);
	WheelLeft->Render(x-8,y+10);
	WheelRight->Render(x+8,y+10);
	connector->Render(x, y+5);
	MainGun->Render(x+15, y);
	DebugOut(L"Main render: %d  %d", x, " ", y);
}

void CMainObject::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MAINOBJECT_STATE_WALKING_RIGHT:
		vx = MAINOBJECT_WALKING_SPEED;
		nx = 1;
		break;
	case MAINOBJECT_STATE_WALKING_LEFT: 
		vx = -MAINOBJECT_WALKING_SPEED;
		nx = -1;
		break;
	case MAINOBJECT_STATE_JUMP: 
		vy = -MAINOBJECT_JUMP_SPEED_Y;

	case MAINOBJECT_STATE_IDLE: 
		vx = 0;
		break;

	case MAINOBJECT_STATE_DOWN:
		vy = MAINOBJECT_JUMP_SPEED_Y;
		break;
	case MAINOBJECT_STATE_STOP:
		vy = vx = 0;
		break;
	}
}
float CMainObject::GetX()
{
	return this->x;
}
float CMainObject::GetY()
{
	return this->y;
}

void CMainObject::LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MAINOBJECT_RIGHT, L"textures\\CarAndMainRight.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_MAINOBJECT_LEFT, L"textures\\CarAndMainLeft.png", D3DCOLOR_XRGB(176, 224, 248));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texMainObjectRight = textures->Get(ID_TEX_MAINOBJECT_RIGHT);
	LPDIRECT3DTEXTURE9 texMainObjectLeft = textures->Get(ID_TEX_MAINOBJECT_LEFT);

	sprites->Add(10001, 355, 3, 371, 11, texMainObjectRight);
	//sprites->Add(10001, 399, 12, 407, 20, texMainObjectRight);
	
	sprites->Add(10011, 39, 3, 55, 11, texMainObjectLeft);

	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);

	CMainObject::AddAnimation(400);		// idle right
	CMainObject::AddAnimation(401);		// idle left

	WheelLeft->LoadResources();
	WheelLeft->SetPosition(this->GetX(), this->GetY());
	WheelRight->LoadResources();
	WheelRight->SetPosition(GetX() + 5, GetY() + 5);
	MainGun->LoadResources();
	MainGun->SetPosition(100.0f, 100.0f);
	connector->LoadResources();
	connector->SetPosition(100.0f, 60.0f);
	DebugOut(L"Main: %d  %d", GetX(), " ", GetY());
}
CMainObject::~CMainObject()
{
	delete WheelLeft;
	delete WheelRight;
	delete connector;
	delete MainGun;
}