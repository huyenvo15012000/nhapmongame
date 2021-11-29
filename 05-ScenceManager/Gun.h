#pragma once
#include "GameObject.h"
#include "Rect.h"
#include "Point.h"

#define GUN_HEIGHT	8
#define GUN_WIDTH	8

#define GUN_ANI_IDLE_RIGHT		0
#define GUN_ANI_IDLE_LEFT		1

#define GUN_STATE_RIGHT		0
#define GUN_STATE_LEFT		1

#define GUN_WALKING_SPEED		0.1f

class Gun : public CGameObject
{
public:
	void Update(DWORD dt);
	virtual void Render();

	void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual Rect GetBoundingBox();
	void Render(float a, float b);

};
