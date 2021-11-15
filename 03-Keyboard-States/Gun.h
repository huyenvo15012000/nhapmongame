#pragma once
#include "GameObject.h"

#define GUN_ANI_IDLE_RIGHT		0
#define GUN_ANI_IDLE_LEFT		1

#define GUN_STATE_RIGHT		0
#define GUN_STATE_LEFT		100

#define GUN_WALKING_SPEED		0.1f

class Gun : public CGameObject
{
public:
	void LoadResources();
	void Update(DWORD dt);
	void Render(float a, float b);
	void SetState(int state);
};
