#pragma once
#include "GameObject.h"

#define ENEMYH_BBOX_WIDTH 22
#define ENEMYH_BBOX_HEIGHT 18

#define ENEMYH_STATE_IDLE 200
#define ENEMYH_STATE_DIE 100
#define ENEMYH_STATE_ITEM 300
#define ENEMYH_UNTOUCHABLE_TIME 			3000
#define ENEMYH_ANI_ITEM 1
#define ENEMYH_ANI_IDLE 0
#define ENEMYH_SPEED 0.1f
class EnemyH : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	float vx = ENEMYH_SPEED;
	float x0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	EnemyH();
	virtual void SetState(int state);
};

