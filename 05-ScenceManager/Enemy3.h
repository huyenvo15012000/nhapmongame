#pragma once
#include "GameObject.h"
#define ENEMY3_WALKING_SPEED 0.05f;

#define ENEMY3_BBOX_WIDTH 16
#define ENEMY3_BBOX_HEIGHT 15
#define ENEMY3_BBOX_HEIGHT_DIE 9

#define ENEMY3_STATE_WALKING 100
#define ENEMY3_STATE_DIE 200

#define ENEMY3_ANI_WALKING 0
#define ENEMY3_ANI_DIE 1
class Enemy3 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy3();
	virtual void SetState(int state);
};