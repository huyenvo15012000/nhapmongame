#include "MainObject.h"
#include "debug.h"

#define TOP_BORDER  0
#define LEFT_BORDER  0
#define BOTTOM_BORDER  SCREEN_HEIGHT - MAINOBJECT_HEIGHT
#define RIGHT_BORDER  SCREEN_WIDTH - MAINOBJECT_WIDTH

void CMainObject::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	/*vy += MAINOBJECT_GRAVITY;
	if (y > 100) 
	{
		vy = 0; y = 100.0f;
	}*/

	//simple screen edge collision!!!
	if (vx > 0 && x > RIGHT_BORDER ) x = RIGHT_BORDER;
	if (vx < 0 && x < LEFT_BORDER) x = LEFT_BORDER;
	if (vy < 0 && y < TOP_BORDER) y = TOP_BORDER;
	if (vy > 0 && y > BOTTOM_BORDER ) y = BOTTOM_BORDER;
}

void CMainObject::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx>0) ani = MAINOBJECT_ANI_IDLE_RIGHT;
		else ani = MAINOBJECT_ANI_IDLE_LEFT;
	}
	else if (vx > 0) 
		ani = MAINOBJECT_ANI_WALKING_RIGHT; 
	else ani = MAINOBJECT_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void CMainObject::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MAINOBJECT_STATE_WALKING_RIGHT:
		vx = MAINOBJECT_WALKING_SPEED;
		nx = 1;
		break;
	case MAINOBJECT_STATE_WALKING_LEFT: 
		vx = -MAINOBJECT_WALKING_SPEED;
		nx = -1;
		break;
	case MAINOBJECT_STATE_JUMP: 
			vy = -MAINOBJECT_JUMP_SPEED_Y;

	case MAINOBJECT_STATE_IDLE: 
		vx = 0;
		break;

	case MAINOBJECT_STATE_DOWN:
		vy = MAINOBJECT_JUMP_SPEED_Y;
		break;
	case MAINOBJECT_STATE_STOP:
		vy = vx = 0;
		break;
	}


}
float CMainObject::GetX()
{
	return this->x;
}
float CMainObject::GetY()
{
	return this->y;
}
