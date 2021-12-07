#include "Bullet.h"
#include "Utils.h"

Bullet::Bullet(int nx)
{
	vx = 0.9*nx;
}
void Bullet::Render()
{/*
	float _x, _y;
	CGame::GetInstance()->GetCamPos(_x, _y);
	if (animation_set->empty()) return;
	if (_x < x + BULLET_WIDTH && x + BULLET_WIDTH < _x + CGame::GetInstance()->GetScreenWidth() * BRICK_BBOX_WIDTH && _y < y && y < _y + CGame::GetInstance()->GetScreenHeight() * BRICK_BBOX_HEIGHT)*/
		animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}


void Bullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_WIDTH;
	b = y + BULLET_HEIGHT;
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//dx = dy = 0;
	CGameObject::Update(dt);

	x += vx*dt;
	//y += 0.1;
}
