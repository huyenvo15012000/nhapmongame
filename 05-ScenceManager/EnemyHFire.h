#pragma once
#include "GameObject.h"
#include "EnemyBullet.h"

#define ENEMYHFIRE_BBOX_WIDTH 22
#define ENEMYHFIRE_BBOX_HEIGHT 18

#define ENEMYHFIRE_STATE_IDLE 200
#define ENEMYHFIRE_STATE_DIE 100
#define ENEMYHFIRE_STATE_ITEM 300
#define ENEMYHFIRE_UNTOUCHABLE_TIME 			3000
#define ENEMYHFIRE_ANI_ITEM 1
#define ENEMYHFIRE_ANI_IDLE 0
#define ENEMYHFIRE_SPEED 0.1f
#define FIRE_TIME	100
class EnemyHFire : public CGameObject
{
	int untouchable;
	EnemyBullet* bullet;
	float x0 = 0;
	int timecount =0;
	float vx = ENEMYHFIRE_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	vector<LPGAMEOBJECT> bullets;
public:
	EnemyHFire();
	void AddBullet(EnemyBullet* bulletF) { bullet = bulletF; };
	void Fire();
	virtual void SetState(int state);
};

