#pragma once
#include "GameObject.h"

#define WHEEL_ANI_IDLE_RIGHT		2
#define WHEEL_ANI_IDLE_LEFT			3
#define WHEEL_ANI_WALKING_RIGHT		4
#define WHEEL_ANI_WALKING_LEFT		5

#define WHEEL_WALKING_SPEED		0.1f

#define WHEEL_STATE_IDLE			0
#define WHEEL_STATE_WALKING_RIGHT	100
#define WHEEL_STATE_WALKING_LEFT	200
#define WHEEL_STATE_JUMP			300
#define WHEEL_STATE_DOWN			400

class Wheel : public CGameObject
{
public:
	void LoadResources();
	void Update(DWORD dt);
	void Render(float a, float b);
	void SetState(int state);
};

