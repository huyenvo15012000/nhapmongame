#pragma once
#include "GameObject.h"
#define ENEMY8_WALKING_SPEED 0.05f;

#define ENEMY8_BBOX_WIDTH 18
#define ENEMY8_BBOX_HEIGHT 18

#define ENEMY8_STATE_WALKING 100
#define ENEMY8_STATE_DIE 200

#define ENEMY8_ANI_WALKING 0
#define ENEMY8_ANI_DIE 1
class Enemy8 : public CGameObject
{
	int x0, y0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy8();
	virtual void SetState(int state);
};