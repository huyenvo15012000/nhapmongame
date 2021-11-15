#pragma once
#include "GameObject.h"

class Connector: public CGameObject
{
public:
		void LoadResources();
		void Update(DWORD dt);
		void Render(float a, float b);
		void SetState(int state);
};

