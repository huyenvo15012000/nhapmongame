#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT_H	10
#define BULLET_WIDTH_H	24
#define BULLET_HEIGHT_U	24
#define BULLET_WIDTH_U	10
#define JASON_BULLET_H	18
#define JASON_BULLET_W	18

#define	BULLET_STATE_DIE	1
#define BULLET_UNTOUCHABLE_TIME 			3000

#define OBJECT_TYPE_BULLET	21


class Bullet : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	int nx, nyy;
	float x0, y1;
	float v1, v2;
	int t;
public:

	bool IsJason = false;
	Bullet(int nx, int ny, int v);
	void SetT(int v) { t = v; };
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void Move();
};