#pragma once
#include "GameObject.h"
#include "Textures.h"

#define ENEMY_WALKING_SPEED		0.1f
#define ENEMY_JUMP_SPEED_Y		0.5f
#define ENEMY_GRAVITY			0.1f

#define ENEMY_STATE_IDLE			0
#define ENEMY_STATE_WALKING_RIGHT	100
#define ENEMY_STATE_WALKING_LEFT	200
#define ENEMY_STATE_JUMP			300
#define ENEMY_STATE_DOWN			400

#define ENEMY_ANI_IDLE_RIGHT		0
#define ENEMY_ANI_IDLE_LEFT		1
#define ENEMY_ANI_WALKING_RIGHT	2
#define ENEMY_ANI_WALKING_LEFT		3

#define ENEMY_HEIGHT				60
#define ENEMY_WIDTH 				40

#define GO_TO_BOTTOM 0
#define GO_TO_LEFT 1
#define GO_TO_TOP 2
#define GO_TO_RIGHT 3
#define START 4

class AutoEnemy : public CGameObject
{
public:
	int CurrentState = GO_TO_BOTTOM;
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	void LoadResources();
};