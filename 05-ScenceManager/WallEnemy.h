#pragma once
#include "GameObject.h"

#define WALLENEMY_BBOX_WIDTH 16
#define WALLENEMY_BBOX_HEIGHT 16

#define WALLENEMY_STATE_IDLE 200
#define WALLENEMY_STATE_DIE 100
#define WALLENEMY_STATE_ITEM 300

#define WALLENEMY_ANI_ITEM 1
#define WALLENEMY_ANI_IDLE 0
class WallEnemy: public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	WallEnemy();
	virtual void SetState(int state);
};

