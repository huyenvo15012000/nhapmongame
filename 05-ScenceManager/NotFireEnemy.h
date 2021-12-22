#pragma once
#include "GameObject.h"

#define NOTFIREENEMY_BBOX_WIDTH 22
#define NOTFIREENEMY_BBOX_HEIGHT 18

#define NOTFIREENEMY_STATE_IDLE 200
#define NOTFIREENEMY_STATE_DIE 100
#define NOTFIREENEMY_STATE_ITEM 300

#define NOTFIREENEMY_ANI_ITEM 1
#define NOTFIREENEMY_ANI_IDLE 0

#define ENEMY_SPEED 0.005f
class NotFireEnemy : public CGameObject
{
	int x0, y0 = 0;
	float vx = vy = ENEMY_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	NotFireEnemy();
	virtual void SetState(int state);
	void MoveToPlayer(float a, float b);
};

