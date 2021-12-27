#pragma once
#include "GameObject.h"

class HealthBar : public CGameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt);
	virtual void Render();
	virtual void SetState(int state) { this->state = state; }
	void Render(float a, float b, int ani_id);
};