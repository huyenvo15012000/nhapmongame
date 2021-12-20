#pragma once
#include "GameObject.h"

#define ENEMYZICZACX_BBOX_WIDTH 22
#define ENEMYZICZACX_BBOX_HEIGHT 18

#define ENEMYZICZACX_STATE_IDLE 200
#define ENEMYZICZACX_STATE_DIE 100
#define ENEMYZICZACX_STATE_ITEM 300

#define ENEMYZICZACX_ANI_ITEM 1
#define ENEMYZICZACX_ANI_IDLE 0

#define ENEMY_SPEED 0.1f
class EnemyZiczacX : public CGameObject
{
	int x0, y0 = 0;
	float vx = vy = ENEMY_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	EnemyZiczacX();
	virtual void SetState(int state);
};

