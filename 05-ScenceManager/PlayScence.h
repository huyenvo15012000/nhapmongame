#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "MainObject.h"
#include "Quadtree.h"

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32

class CPlayScene: public CScene
{
protected: 
	CMainObject *player;					// A play scene has to have player, right? 
	//Camera *camera;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	Quadtree* CreateQuadtree(vector<LPGAMEOBJECT> list, Point p);
	void UpdateActObj(Point p);
	void UpdateObj(CGameObject* obj, DWORD dt);

	CMainObject* GetPlayer() { return player; };
	//Camera * GetCamera() { return camera; }
	//friend class CPlayScenceKeyHandler;
	
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

