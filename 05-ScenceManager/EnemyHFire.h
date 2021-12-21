#pragma once
#include "GameObject.h"

#define ENEMYHFIRE_BBOX_WIDTH 22
#define ENEMYHFIRE_BBOX_HEIGHT 18

#define ENEMYHFIRE_STATE_IDLE 200
#define ENEMYHFIRE_STATE_DIE 100
#define ENEMYHFIRE_STATE_ITEM 300
#define ENEMYHFIRE_UNTOUCHABLE_TIME 			3000
#define ENEMYHFIRE_ANI_ITEM 1
#define ENEMYHFIRE_ANI_IDLE 0
#define ENEMYHFIRE_SPEED 0.1f
class EnemyHFire : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	float vx = ENEMYHFIRE_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	EnemyHFire();
	virtual void SetState(int state);
};

