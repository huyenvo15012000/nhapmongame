#include "AutoEnemy.h"
#include "debug.h"
#include <stdio.h>



void AutoEnemy::Update(DWORD dt)
{
	CGameObject::Update(dt);

	if (x > SCREEN_WIDTH - ENEMY_WIDTH)
	{
		this->SetState(GO_TO_BOTTOM);
	}
	else
		if (y > SCREEN_HEIGHT - ENEMY_HEIGHT)
		{
			this->SetState(GO_TO_LEFT);
		}
		else
			if (x < 0)
			{
				this->SetState(GO_TO_TOP);
			}
			else
				if (y < 0)
				{
					this->SetState(GO_TO_RIGHT);
				}
				else
					this->SetState(this->CurrentState);

}

void AutoEnemy::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) ani = ENEMY_ANI_IDLE_RIGHT;
		else ani = ENEMY_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = ENEMY_ANI_WALKING_RIGHT;
	else ani = ENEMY_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void AutoEnemy::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GO_TO_BOTTOM:
		this->CurrentState = GO_TO_BOTTOM;
		vx = -ENEMY_WALKING_SPEED;
		vy = ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;
	case GO_TO_LEFT:
		/*vx = -MAINOBJECT_WALKING_SPEED;
		nx = -1;
		break;*/
		this->CurrentState = GO_TO_LEFT;
		vx = -ENEMY_WALKING_SPEED;
		vy = -ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;
	case GO_TO_TOP:
		//vy = -MAINOBJECT_JUMP_SPEED_Y;
		this->CurrentState = GO_TO_TOP;
		vx = ENEMY_WALKING_SPEED;
		vy = -ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;

	case GO_TO_RIGHT:
		//vx = 0;
		this->CurrentState = GO_TO_RIGHT;
		vx = ENEMY_WALKING_SPEED;
		vy = ENEMY_WALKING_SPEED;
		x += vx*10;
		y += vy*10;
		break;
		break;
	}



}

