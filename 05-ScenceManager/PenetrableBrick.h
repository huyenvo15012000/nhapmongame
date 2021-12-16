#pragma once
#include "GameObject.h"
class PenetrableBrick: public CGameObject
{
	public:
		PenetrableBrick() {
			IsPenetrable = true;
		}
		virtual void Render();
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};

