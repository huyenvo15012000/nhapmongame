#pragma once
#include "GameObject.h"
#define ENEMY10_WALKING_SPEED 0.05f;

#define ENEMY10_BBOX_WIDTH 16
#define ENEMY10_BBOX_HEIGHT 15

#define ENEMY10_STATE_WALKING 100
#define ENEMY10_STATE_DIE 200

#define ENEMY10_ANI_WALKING 0
#define ENEMY10_ANI_DIE 1
class Enemy10 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy10();
	virtual void SetState(int state);
};