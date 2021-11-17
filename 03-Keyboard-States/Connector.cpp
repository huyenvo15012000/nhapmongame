#include "Connector.h"
#include "debug.h"
#include "Textures.h"

#define ID_TEX_CONNECTOR		20

void Connector::Update(DWORD dt)
{
	CGameObject::Update(dt);
	//x += vx * dt;
	//y += vy * dt;
}

void Connector::Render(float a, float b)
{
	animations[12]->Render(a, b);
}

void Connector::SetState(int state)
{
	CGameObject::SetState(state);
}

void Connector::LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_CONNECTOR, L"textures\\CarAndMainLeft.png", D3DCOLOR_XRGB(176, 224, 248));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texConnector = textures->Get(ID_TEX_CONNECTOR);

	sprites->Add(20001, 39, 21, 47, 29, texConnector);

	LPANIMATION ani;

	ani = new CAnimation(200);
	ani->Add(20001);
	animations->Add(2400, ani);
	Connector::AddAnimation(2400);
	
}
Rect Connector::GetBoundingBox()
{
	return Rect(Point(x, y + 6), CONNECTOR_WIDTH - 1, CONNECTOR_HEIGHT - 1);
}