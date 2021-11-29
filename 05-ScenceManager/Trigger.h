#pragma once
#include "GameObject.h"
#include "Brick.h"
class Trigger : public CBrick
{
	vector<LPGAMEOBJECT>* enemies;
public:
	bool isTrigg = false;
	void Reset();
	void setEnemies(LPGAMEOBJECT e) { enemies->push_back(e); }
	void setEnemies(vector<LPGAMEOBJECT>* _enemies) { enemies = _enemies; }
	vector<LPGAMEOBJECT>* getEnemies() { return enemies; }
	void TriggEnemies();
	Trigger();
};
