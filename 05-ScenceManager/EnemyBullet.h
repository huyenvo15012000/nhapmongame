#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT_H	10
#define BULLET_WIDTH_H	24
#define BULLET_HEIGHT_U	24
#define BULLET_WIDTH_U	10

#define	BULLET_STATE_DIE	1
#define BULLET_UNTOUCHABLE_TIME 			5000

#define OBJECT_TYPE_BULLET	21


class EnemyBullet : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	int nx, nyy;
public:
	EnemyBullet(int nx, int ny);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};