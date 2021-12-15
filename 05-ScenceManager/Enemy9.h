#pragma once
#include "GameObject.h"
#define ENEMY9_WALKING_SPEED 0.05f;

#define ENEMY9_BBOX_WIDTH 18
#define ENEMY9_BBOX_HEIGHT 18
#define ENEMY9_BBOX_HEIGHT_DIE 9

#define ENEMY9_STATE_WALKING 100
#define ENEMY9_STATE_DIE 200

#define ENEMY9_ANI_WALKING 0
#define ENEMY9_ANI_DIE 1
class Enemy9 : public CGameObject
{
	int x0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy9();
	virtual void SetState(int state);
};