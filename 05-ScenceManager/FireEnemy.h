#pragma once
#include "GameObject.h"
#include "EnemyBullet.h"

#define FIREENEMY_BBOX_WIDTH 20
#define FIREENEMY_BBOX_HEIGHT 20

#define FIREENEMY_STATE_IDLE 200
#define FIREENEMY_STATE_DIE 100
#define FIREENEMY_STATE_ITEM 300

#define FIREENEMY_ANI_ITEM 1
#define FIREENEMY_ANI_IDLE 0
#define MAINOBJECT_UNTOUCHABLE_TIME 			1000

#define ENEMY_SPEED 0.007f
class FireEnemy : public CGameObject
{
	int x0, y0 = 0;
	EnemyBullet* bullet;
	int timecount;
	int untouchable;
	vector<LPGAMEOBJECT> bullets;
	DWORD untouchable_start;
	float vx;
	float vy = ENEMY_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	FireEnemy();
	void Fire();
	void AddBullet(EnemyBullet* bulletF) { bullet = bulletF; };
	virtual void SetState(int state);
	void MoveToPlayer(float a, float b);
};

