#pragma once
#include "GameObject.h"

#define MAINOBJECT_WALKING_SPEED		0.1f
#define MAINOBJECT_JUMP_SPEED_Y		0.1f
#define MAINOBJECT_GRAVITY			0.1f

#define MAINOBJECT_STATE_IDLE			0
#define MAINOBJECT_STATE_WALKING_RIGHT	100
#define MAINOBJECT_STATE_WALKING_LEFT	200
#define MAINOBJECT_STATE_JUMP			300
#define MAINOBJECT_STATE_DOWN			400
#define	MAINOBJECT_STATE_STOP			500

#define MAINOBJECT_ANI_IDLE_RIGHT		0
#define MAINOBJECT_ANI_IDLE_LEFT		1
#define MAINOBJECT_ANI_WALKING_RIGHT	2
#define MAINOBJECT_ANI_WALKING_LEFT		3
#define MAINOBJECT_IS_ON_LEFTTOP		4

#define MAINOBJECT_HEIGHT				60
#define MAINOBJECT_WIDTH 				40

class CMainObject : public CGameObject
{
public: 

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	float GetX();
	float GetY();
};