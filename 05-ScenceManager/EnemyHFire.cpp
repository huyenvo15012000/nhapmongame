#include "EnemyHFire.h"
#include "Utils.h"
#include "Brick2.h"
#include "PenetrableBrick.h"
#include "EnemyBullet.h"
EnemyHFire::EnemyHFire()
{
	state = ENEMYHFIRE_STATE_IDLE;
}

void EnemyHFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMYHFIRE_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMYHFIRE_BBOX_WIDTH;
	bottom = y + ENEMYHFIRE_BBOX_HEIGHT;
}

void EnemyHFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin() + i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	x += vx * dt;
	if (x0 == 0)
		x0 = x;
	if (x < x0-200 && vx < 0)
	{
		x = x0 - 200;
		vx = -vx;
	}
	if (x > x0 && vx > 0)
	{
		x = x0;
		vx = -vx;
	}
	timecount++;
	
	if (timecount >= 100)
	{
		Fire();
		timecount = 0;
	}
		
}

void EnemyHFire::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMYHFIRE_ANI_IDLE;
	if (state == ENEMYHFIRE_STATE_ITEM) {
		ani = ENEMYHFIRE_ANI_ITEM;
	}
	if (state == ENEMYHFIRE_STATE_DIE)
	{
		return;
	}
	for (int i = 0; i < bullets.size();i++)
		bullets[i]->Render();
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void EnemyHFire::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMYHFIRE_STATE_DIE:
		DebugOut(L"EnemyHFire die");
		break;
	}
}

void EnemyHFire::Fire()
{
	EnemyBullet* newBullet;
	newBullet = new EnemyBullet(0,0);
	newBullet->SetAnimationSet(bullet->animation_set);
	newBullet->SetPosition(x, y);
	bullets.push_back(newBullet);
	//DebugOut(L"Bulet %d \n", bullets.size());
}