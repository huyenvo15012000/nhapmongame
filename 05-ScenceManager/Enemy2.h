#pragma once
#include "GameObject.h"
#define ENEMY2_WALKING_SPEED 0.05f;

#define ENEMY2_BBOX_WIDTH 16
#define ENEMY2_BBOX_HEIGHT 15

#define ENEMY2_STATE_WALKING 100
#define ENEMY2_STATE_DIE 200

#define ENEMY2_ANI_WALKING 0
#define ENEMY2_ANI_DIE 1
class Enemy2 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy2();
	virtual void SetState(int state);
};