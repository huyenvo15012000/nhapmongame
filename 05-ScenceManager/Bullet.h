#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT	8
#define BULLET_WIDTH	24

#define	BULLET_STATE_DIE	1
#define BULLET_UNTOUCHABLE_TIME 			5000

class Bullet : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
public:
	Bullet(int nx);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};