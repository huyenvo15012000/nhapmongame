#pragma once
#include "GameObject.h"
#include "Gun.h"
#include "Wheel.h"
#include "Connector.h"
#include "Rect.h"
#include "Point.h"

#define MAINOBJECT_WALKING_SPEED		0.1f
#define MAINOBJECT_JUMP_SPEED_Y		0.1f
#define MAINOBJECT_GRAVITY			-0.1f

#define MAINOBJECT_STATE_IDLE			0
#define MAINOBJECT_STATE_WALKING_RIGHT	100
#define MAINOBJECT_STATE_WALKING_LEFT	200
#define MAINOBJECT_STATE_JUMP			300
#define MAINOBJECT_STATE_DOWN			400
#define	MAINOBJECT_STATE_STOP			500
#define MAINOBJECT_HAVE_GUN				600
#define MAINOBJECT_NO_GUN				700
#define MAINOBJECT_STATE_DIE			800

#define MAINOBJECT_ANI_IDLE_RIGHT		1
#define MAINOBJECT_ANI_IDLE_LEFT		0
#define MAINOBJECT_ANI_WALKING_RIGHT	2
#define MAINOBJECT_ANI_WALKING_LEFT		3


#define MAINOBJECT_HEIGHT				50
#define MAINOBJECT_WIDTH 				40
#define MAINOBJECT_BBOX_HEIGHT			20
#define MAINOBJECT_BBOX_WIDTH 			25
#define MAINOBJECT_UNTOUCHABLE_TIME 			5000

#define TOP_BORDER  40
#define LEFT_BORDER  15
#define BOTTOM_BORDER  520- MAINOBJECT_HEIGHT
#define RIGHT_BORDER  1232 - MAINOBJECT_WIDTH

class CMainObject : public CGameObject
{
protected:
	Wheel* WheelLeft, * WheelRight;
	Gun* MainGun;
	Connector* connector;
	int untouchable;
	DWORD untouchable_start;
	bool IsCollide = false;

	float start_x;			// initial position of Mario at scene
	float start_y;
	~CMainObject();
public:
	CMainObject();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void addGun(Gun* gunF);
	void addConnector(Connector* connectorF);
	void addWheel(Wheel* wheelF);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CMainObject(float x = 0.0f, float y = 0.0f);
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; this->yWorld = 496 - y; }
};



