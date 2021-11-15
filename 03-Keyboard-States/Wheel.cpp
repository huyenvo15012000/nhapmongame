#include "Wheel.h"
#include "debug.h"
#include "Textures.h"

#define ID_TEX_WHEEL_RIGHT			40
#define ID_TEX_WHEEL_LEFT 			41

void Wheel::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void Wheel::Render(float a, float b)
{
	int ani;
	if (nx > 0) ani = WHEEL_ANI_IDLE_RIGHT;
	else ani = WHEEL_ANI_IDLE_LEFT;
	animations[ani]->Render(a, b);
}

void Wheel::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHEEL_STATE_WALKING_RIGHT:
		vx = WHEEL_WALKING_SPEED;
		nx = 1;
		break;
	case WHEEL_STATE_WALKING_LEFT:
		vx = -WHEEL_WALKING_SPEED;
		nx = -1;
		break;
	case WHEEL_STATE_JUMP:
		vy = -WHEEL_WALKING_SPEED;

	case WHEEL_STATE_IDLE:
		vx = 0;
		break;

	case WHEEL_STATE_DOWN:
		vy = WHEEL_WALKING_SPEED;
		break;
	}


}

void Wheel::LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_WHEEL_RIGHT, L"textures\\CarAndMainRight.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_WHEEL_LEFT, L"textures\\CarAndMainLeft.png", D3DCOLOR_XRGB(176, 224, 248));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texWheelRight = textures->Get(ID_TEX_WHEEL_RIGHT);
	LPDIRECT3DTEXTURE9 texWheelLeft = textures->Get(ID_TEX_WHEEL_LEFT);

	sprites->Add(10001, 390, 21, 398, 29, texWheelRight);

	sprites->Add(10002, 399, 21, 407, 29, texWheelRight);
	sprites->Add(10003, 372, 21, 380, 29, texWheelRight);
	sprites->Add(10004, 381, 21, 389, 29, texWheelRight);
	

	sprites->Add(10011, 12, 21, 20, 29, texWheelLeft);

	sprites->Add(10012, 3, 21, 11, 29, texWheelLeft);
	sprites->Add(10013, 30, 21, 38, 29, texWheelLeft);
	sprites->Add(10014, 21, 21, 29, 29, texWheelLeft);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(501, ani);

	Wheel::AddAnimation(400);		// idle right
	Wheel::AddAnimation(401);		// idle left
	Wheel::AddAnimation(500);		// walk right
	Wheel::AddAnimation(501);		// walk left

}
