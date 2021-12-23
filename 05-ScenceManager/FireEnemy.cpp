#include "FireEnemy.h"
#include "Brick2.h"
#include "Utils.h"

float u0, u1;
FireEnemy::FireEnemy()
{
	state = FIREENEMY_STATE_IDLE;
}

void FireEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + FIREENEMY_BBOX_WIDTH;
	bottom = y + FIREENEMY_BBOX_HEIGHT;
}

void FireEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float player_x, player_y;
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin() + i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	coObjects->at(coObjects->size() - 1)->GetPosition(player_x, player_y);
	float distance = sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	//coObjects->pop_back();
	// turn off collision when die 
	if (state != FIREENEMY_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		vx = vy = ENEMY_SPEED;
		if (distance <= 100)
			MoveToPlayer(player_x, player_y);
		//DebugOut(L"Move X: %d, Y: %d , D: %f \n", int(player_x), int(player_y), distance);
	}
	else
	{
		//vx = vy = 0.0f;
		
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		/*vx = ENEMY_SPEED;
		vy = 0;*/
		
		//DebugOut(L"Enemy coll: %f   %f", float(vx), float(vy));
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			try {
				if (dynamic_cast<Brick2*>(e->obj))
				{
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}			
			}
			catch (exception e) {

			}
		}
	}
	timecount++;

	if (timecount >= 100)
	{
		Fire();
		timecount = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"X: %d, Y: %d \n", int(x), int(y));
}
	


void FireEnemy::MoveToPlayer(float a, float b)
{
	//DebugOut(L"Move X: %f, Y: %f \n", vx, vy);
	u0 = a - x;
	u1 = b - y;
	x += vx * u0;
	y += vy * u1;
}
void FireEnemy::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = get_hit;
	/*if (state == FIREENEMY_STATE_ITEM) {
		ani = FIREENEMY_ANI_ITEM;
	}*/
	if (state == STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);
	for (int i = 0; i < bullets.size();i++)
		bullets[i]->Render();
}

void FireEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREENEMY_STATE_DIE:
		DebugOut(L"FireEnemy die");
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}
void FireEnemy::Fire()
{
	EnemyBullet* newBullet;
	newBullet = new EnemyBullet(u0/abs(u0), u1/abs(u1));
	newBullet->SetAnimationSet(bullet->animation_set);
	newBullet->SetPosition(x, y);
	bullets.push_back(newBullet);
	DebugOut(L"Bulet Fire \n", bullets.size());
}