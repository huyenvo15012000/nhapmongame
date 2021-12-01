#pragma once
#include "GameObject.h"
#define ENEMY4_WALKING_SPEED 0.05f;

#define ENEMY4_BBOX_WIDTH 16
#define ENEMY4_BBOX_HEIGHT 15
#define ENEMY4_BBOX_HEIGHT_DIE 9

#define ENEMY4_STATE_WALKING 100
#define ENEMY4_STATE_DIE 200

#define ENEMY4_ANI_WALKING 0
#define ENEMY4_ANI_DIE 1
class Enemy4 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy4();
	virtual void SetState(int state);
};