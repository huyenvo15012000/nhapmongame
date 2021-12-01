#pragma once
#include "GameObject.h"
#define ENEMY7_WALKING_SPEED 0.05f;

#define ENEMY7_BBOX_WIDTH 16
#define ENEMY7_BBOX_HEIGHT 15
#define ENEMY7_BBOX_HEIGHT_DIE 9

#define ENEMY7_STATE_WALKING 100
#define ENEMY7_STATE_DIE 200

#define ENEMY7_ANI_WALKING 0
#define ENEMY7_ANI_DIE 1
class Enemy7 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy7();
	virtual void SetState(int state);
};