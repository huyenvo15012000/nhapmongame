#pragma once
#include "GameObject.h"
#include "Rect.h"
#include "Point.h"

#define CONNECTOR_HEIGHT	8
#define CONNECTOR_WIDTH		8

class Connector: public CGameObject
{
public:
		void LoadResources();
		void Update(DWORD dt);
		void Render(float a, float b);
		void SetState(int state);
		Rect GetBoundingBox();
};

