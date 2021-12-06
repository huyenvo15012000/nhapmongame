#pragma once
#include "GameObject.h"
#include "Game.h"

#define BULLET_HEIGHT	8
#define BULLET_WIDTH	24

class Bullet : public CGameObject
{
public:
	virtual Bullet* clone() const { return new Bullet(*this); }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
