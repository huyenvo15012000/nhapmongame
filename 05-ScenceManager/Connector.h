#pragma once
#include "GameObject.h"
#include "Rect.h"
#include "Point.h"

#define CONNECTOR_HEIGHT	8
#define CONNECTOR_WIDTH		8
#define OBJECT_TYPE_CONNECTOR	3
class Connector : public CGameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt);
	virtual void Render();
	virtual void SetState(int state) { this->state = state; }
	void Render(float a, float b);
};

