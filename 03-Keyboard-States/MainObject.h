#pragma once
#include "GameObject.h"
#include "Gun.h"
#include "Wheel.h"
#include "Connector.h"

#define MAINOBJECT_WALKING_SPEED		0.1f
#define MAINOBJECT_JUMP_SPEED_Y		0.1f
#define MAINOBJECT_GRAVITY			0.1f

#define MAINOBJECT_STATE_IDLE			0
#define MAINOBJECT_STATE_WALKING_RIGHT	100
#define MAINOBJECT_STATE_WALKING_LEFT	200
#define MAINOBJECT_STATE_JUMP			300
#define MAINOBJECT_STATE_DOWN			400
#define	MAINOBJECT_STATE_STOP			500
#define MAINOBJECT_HAVE_GUN				600
#define MAINOBJECT_NO_GUN				700

#define MAINOBJECT_ANI_IDLE_RIGHT		0
#define MAINOBJECT_ANI_IDLE_LEFT		1
#define MAINOBJECT_ANI_WALKING_RIGHT	2
#define MAINOBJECT_ANI_WALKING_LEFT		3


#define MAINOBJECT_HEIGHT				60
#define MAINOBJECT_WIDTH 				40

#define TOP_BORDER  0
#define LEFT_BORDER  0
#define BOTTOM_BORDER  SCREEN_HEIGHT - MAINOBJECT_HEIGHT
#define RIGHT_BORDER  SCREEN_WIDTH - MAINOBJECT_WIDTH

class CMainObject : public CGameObject
{
protected:
	Wheel* WheelLeft, * WheelRight;
	Gun* MainGun;
	Connector* connector;
	~CMainObject();
public:
	CMainObject();
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	float GetX();
	float GetY();
};



