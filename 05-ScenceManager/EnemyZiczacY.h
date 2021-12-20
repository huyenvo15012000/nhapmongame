#pragma once
#include "GameObject.h"

#define ENEMYZICZACY_BBOX_WIDTH 22
#define ENEMYZICZACY_BBOX_HEIGHT 18

#define ENEMYZICZACY_STATE_IDLE 200
#define ENEMYZICZACY_STATE_DIE 100
#define ENEMYZICZACY_STATE_ITEM 300

#define ENEMYZICZACY_ANI_ITEM 1
#define ENEMYZICZACY_ANI_IDLE 0

#define ENEMY_SPEED 0.1f
class EnemyZiczacY : public CGameObject
{
	int x0, y0 = 0;
	float vx = vy = ENEMY_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	EnemyZiczacY();
	virtual void SetState(int state);
};

