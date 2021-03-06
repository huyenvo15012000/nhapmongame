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
#include "SmallJason.h"

#define MAINOBJECT_WALKING_SPEED		0.15f
#define MAINOBJECT_JUMP_SPEED_Y		0.5f
#define MAINOBJECT_GRAVITY			-0.005f

#define MAINOBJECT_STATE_IDLE			0
#define MAINOBJECT_STATE_WALKING_RIGHT	100
#define MAINOBJECT_STATE_WALKING_LEFT	200
#define MAINOBJECT_STATE_WALKING_UP	101
#define MAINOBJECT_STATE_WALKING_DOWN	201
#define MAINOBJECT_STATE_JUMP			300
#define MAINOBJECT_STATE_DOWN			400
#define	MAINOBJECT_STATE_STOP			500
#define MAINOBJECT_HAVE_GUN				600
#define MAINOBJECT_NO_GUN				700
#define MAINOBJECT_STATE_DIE			800
#define MAINOBJECT_HEALTH			8
#define MAINOBJECT_STATE_FIRE		900
#define MAINOBJECT_STATE_FIRE_UP		1000

#define MAINOBJECT_ANI_IDLE_RIGHT		1
#define MAINOBJECT_ANI_IDLE_LEFT		0
#define JASON_ANI_IDLE		0
#define JASON_ANI_BACK		1
#define MAINOBJECT_ANI_WALKING_RIGHT	3
#define MAINOBJECT_ANI_WALKING_LEFT		2
#define MAINOBJECT_ANI_FIRE_UP_LEFT	2
#define MAINOBJECT_ANI_FIRE_UP_RIGHT	3
#define BULLET_NUMBER	6


#define MAINOBJECT_HEIGHT				30
#define MAINOBJECT_WIDTH 				30
#define MAINOBJECT_BBOX_HEIGHT			17
#define MAINOBJECT_BBOX_WIDTH 			25
#define JASON_BBOX_HEIGHT			15
#define JASON_BBOX_WIDTH 			15
#define MAINOBJECT_UNTOUCHABLE_TIME 			5000
#define MAINOBJECT_AMOUNT_BULLET				1

#define TOP_BORDER  40
#define LEFT_BORDER  15
#define BOTTOM_BORDER  520- MAINOBJECT_HEIGHT
#define RIGHT_BORDER  1232 - MAINOBJECT_WIDTH

class CMainObject : public CGameObject
{
protected:
	bool isJason = false;
	Wheel* WheelLeft, * WheelRight;
	Gun* MainGun;
	Connector* connector;
	Bullet* bullet;
	SmallJason* jason;
	int untouchable;
	DWORD untouchable_start;
	bool IsCollide = false;
	int create_bullet_count;
	float start_x;			// initial position of Mario at scene
	float start_y;
	int nyy;
	vector<LPGAMEOBJECT> bullets;
	~CMainObject();
public:
	CMainObject();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetJason() { isJason = true; }
	bool IsJason() { return isJason; }
	void SetState(int state);
	void addGun(Gun* gunF);
	void addConnector(Connector* connectorF);
	void addWheel(Wheel* wheelF);
	void addBullet(Bullet* bulletF);
	void addJason(SmallJason* js) { jason = js; };

	void Fire();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void Reset();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CMainObject(float x = 0.0f, float y = 0.0f);
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
};


