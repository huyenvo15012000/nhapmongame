#pragma once
#pragma warning
#include "GameObject.h"
#include "Gun.h"
#include "Wheel.h"
#include "Connector.h"
#include "Rect.h"
#include "Point.h"
#include "Bullet.h"
#include "HealthBar.h"

#define JASON_WALKING_SPEED		0.05f
#define JASON_JUMP_SPEED_Y		0.5f
#define JASON_GRAVITY			-0.009f

#define JASON_STATE_WALKING	100
#define JASON_STATE_JUMP			300

#define JASON_ANI_JUMP		0
#define JASON_ANI_WALK		1

#define JASON_BBOX_HEIGHT			17
#define JASON_BBOX_WIDTH 			16
#define JASON_UNTOUCHABLE_TIME 			5000=


class SmallJason : public CGameObject
{
protected:
	int untouchable;
	DWORD untouchable_start;
	float start_x;			// initial position of Mario at scene
	float start_y;
	int nyy;
	vector<LPGAMEOBJECT> bullets;
	~SmallJason();
public:
	bool Active = false;
	SmallJason();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void SetState(int state);

	void Reset();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	SmallJason(float x = 0.0f, float y = 0.0f);
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
};


