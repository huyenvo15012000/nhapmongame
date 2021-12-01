#pragma once
#include "GameObject.h"
#define ENEMY5_WALKING_SPEED 0.05f;

#define ENEMY5_BBOX_WIDTH 16
#define ENEMY5_BBOX_HEIGHT 15
#define ENEMY5_BBOX_HEIGHT_DIE 9

#define ENEMY5_STATE_WALKING 100
#define ENEMY5_STATE_DIE 200

#define ENEMY5_ANI_WALKING 0
#define ENEMY5_ANI_DIE 1
class Enemy5 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy5();
	virtual void SetState(int state);
};