#pragma once
#include "GameObject.h"

#define ENEMY1_BBOX_WIDTH 16
#define ENEMY1_BBOX_HEIGHT 15

#define ENEMY1_STATE_IDLE 200
#define ENEMY1_STATE_DIE 200

#define ENEMY1_ANI_DIE 1
#define ENEMY1_ANI_IDLE 0
class Enemy1 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy1();
	virtual void SetState(int state);
};

