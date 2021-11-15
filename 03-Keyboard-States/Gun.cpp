#include "Gun.h"
#include "debug.h"
#include "Textures.h"

#define ID_TEX_GUN_RIGHT			30
#define ID_TEX_GUN_LEFT 			31

void Gun::Update(DWORD dt)
{
	CGameObject::Update(dt);
	/*x += GUN_WALKING_SPEED * dt;
	y += GUN_WALKING_SPEED * dt;*/
}

void Gun::Render(float a, float b)
{
	int ani;
	if (nx > 0) ani = GUN_ANI_IDLE_RIGHT;
	else ani = GUN_ANI_IDLE_LEFT;
	animations[10]->Render(a, b);
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

void Gun::LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_GUN_RIGHT, L"textures\\CarAndMainRight.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_GUN_LEFT, L"textures\\CarAndMainLeft.png", D3DCOLOR_XRGB(176, 224, 248));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texGunRight = textures->Get(ID_TEX_GUN_RIGHT);
	LPDIRECT3DTEXTURE9 texGunLeft = textures->Get(ID_TEX_GUN_LEFT);

	sprites->Add(10001, 390, 3, 398, 11, texGunRight);

	/*sprites->Add(10002, 178, 5, 204, 23, texGun);
	sprites->Add(10003, 211, 5, 237, 23, texGun);
	sprites->Add(10004, 241, 5, 267, 23, texGun);*/

	sprites->Add(10011, 12, 3, 20, 11, texGunLeft);

	/*sprites->Add(10012, 77, 5, 103, 23, texGun);
	sprites->Add(10013, 44, 5, 70, 23, texGun);
	sprites->Add(10014, 13, 5, 39, 23, texGun);*/


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	//ani = new CAnimation(100);
	//ani->Add(10001);
	//ani->Add(10002);
	//ani->Add(10003);
	//ani->Add(10004);
	//animations->Add(500, ani);

	//ani = new CAnimation(100);
	//ani->Add(10011);
	//ani->Add(10012);
	//ani->Add(10013);
	//ani->Add(10014);
	//animations->Add(501, ani);

	Gun::AddAnimation(400);		// idle right
	Gun::AddAnimation(401);		// idle left
	//CGun::AddAnimation(500);		// walk right
	//CGun::AddAnimation(501);		// walk left

}
