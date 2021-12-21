#pragma once
#include "GameObject.h"

#define FIREENEMY_BBOX_WIDTH 22
#define FIREENEMY_BBOX_HEIGHT 18

#define FIREENEMY_STATE_IDLE 200
#define FIREENEMY_STATE_DIE 100
#define FIREENEMY_STATE_ITEM 300

#define FIREENEMY_ANI_ITEM 1
#define FIREENEMY_ANI_IDLE 0

#define ENEMY_SPEED 0.001f
class FireEnemy : public CGameObject
{
	int x0, y0 = 0;
	float vx = vy = ENEMY_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	FireEnemy();
	virtual void SetState(int state);
	void MoveToPlayer(float a, float b);
};

