#pragma once
#include "GameObject.h"
#define ENEMY6_WALKING_SPEED 0.05f;

#define ENEMY6_BBOX_WIDTH 16
#define ENEMY6_BBOX_HEIGHT 15
#define ENEMY6_BBOX_HEIGHT_DIE 9

#define ENEMY6_STATE_WALKING 100
#define ENEMY6_STATE_DIE 200

#define ENEMY6_ANI_WALKING 0
#define ENEMY6_ANI_DIE 1
class Enemy6 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy6();
	virtual void SetState(int state);
};