#include "AutoEnemy.h"
#include "debug.h"
#include <stdio.h>
#include "Textures.h"


void AutoEnemy::Update(DWORD dt)
{
	CGameObject::Update(dt);
	//nothing
	if (x > SCREEN_WIDTH - ENEMY_WIDTH)
	{
		this->SetState(GO_TO_BOTTOM);
	}
	else
		if (y > SCREEN_HEIGHT - ENEMY_HEIGHT)
		{
			this->SetState(GO_TO_LEFT);
		}
		else
			if (x < 0)
			{
				this->SetState(GO_TO_TOP);
			}
			else
				if (y < 0)
				{
					this->SetState(GO_TO_RIGHT);
				}
				else
					this->SetState(this->CurrentState);

}

void AutoEnemy::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) ani = ENEMY_ANI_IDLE_RIGHT;
		else ani = ENEMY_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = ENEMY_ANI_WALKING_RIGHT;
	else ani = ENEMY_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void AutoEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GO_TO_BOTTOM:
		this->CurrentState = GO_TO_BOTTOM;
		vx = -ENEMY_WALKING_SPEED;
		vy = ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;
	case GO_TO_LEFT:
		/*vx = -MAINOBJECT_WALKING_SPEED;
		nx = -1;
		break;*/
		this->CurrentState = GO_TO_LEFT;
		vx = -ENEMY_WALKING_SPEED;
		vy = -ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;
	case GO_TO_TOP:
		//vy = -MAINOBJECT_JUMP_SPEED_Y;
		this->CurrentState = GO_TO_TOP;
		vx = ENEMY_WALKING_SPEED;
		vy = -ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;

	case GO_TO_RIGHT:
		//vx = 0;
		this->CurrentState = GO_TO_RIGHT;
		vx = ENEMY_WALKING_SPEED;
		vy = ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;
		break;
	}
}

void AutoEnemy::LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	/*textures->Add(ID_TEX_MAINOBJECT_RIGHT, L"textures\\CarAndMainRight.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_MAINOBJECT_LEFT, L"textures\\CarAndMainLeft.png", D3DCOLOR_XRGB(176, 224, 248));*/

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	/*LPDIRECT3DTEXTURE9 texMainObjectRight = textures->Get(ID_TEX_MAINOBJECT_RIGHT);
	LPDIRECT3DTEXTURE9 texMainObjectLeft = textures->Get(ID_TEX_MAINOBJECT_LEFT);

	sprites->Add(10001, 146, 5, 172, 23, texMainObjectRight);

	sprites->Add(10002, 178, 5, 204, 23, texMainObject);
	sprites->Add(10003, 211, 5, 237, 23, texMainObject);
	sprites->Add(10004, 241, 5, 267, 23, texMainObject);

	sprites->Add(10011, 109, 5, 135, 23, texMainObject);

	sprites->Add(10012, 77, 5, 103, 23, texMainObject);
	sprites->Add(10013, 44, 5, 70, 23, texMainObject);
	sprites->Add(10014, 13, 5, 39, 23, texMainObject);*/


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

	AutoEnemy::AddAnimation(400);		// idle right
	AutoEnemy::AddAnimation(401);		// idle left
	AutoEnemy::AddAnimation(500);		// walk right
	AutoEnemy::AddAnimation(501);		// walk left

}
Rect AutoEnemy::GetBoundingBox()
{
	return Rect(Point(x, y + 6), ENEMY_WIDTH - 1, ENEMY_HEIGHT - 1);
}