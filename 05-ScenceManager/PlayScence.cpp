#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Quadtree.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MAINOBJECT	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


vector<vector<int>> MapTile;
vector<vector<vector<int>>> MapObj;
vector<LPGAMEOBJECT> objects, screenObj, actObj, moveObj;
vector<LPGAMEOBJECT>* coObj = new vector<LPGAMEOBJECT>();

LPDIRECT3DTEXTURE9 texMap1;
int lx, ly;
int Stage;
Point tf, br;
Quadtree* quadtree;

Quadtree* CPlayScene::CreateQuadtree(vector<LPGAMEOBJECT> list, Point p)
{
	// Init base game region for detecting collision
	Quadtree* quadtree = new Quadtree(1, new Rect(p - Point(5, 5) * 16, p + Point(5, 5) * 16));
	for (auto i = list.begin(); i != list.end(); i++)
		quadtree->Insert(*i);

	return quadtree;
}
void CPlayScene::UpdateActObj(Point p) {
	float cx = p.x, cy = p.y;
	int stx = int(cx / BRICK_HEIGHT) - 5, sty = int(cy / BRICK_WIDTH) - 5;
	if (stx < 0) stx = 0;
	if (sty < 0) sty = 0;
	actObj.clear();
	for (int y = sty; y < sty + 5 + SCREEN_HEIGHT / BRICK_HEIGHT && y < MapTile.size(); y++) {
		for (int x = stx; x < stx + 5 + SCREEN_WIDTH / BRICK_WIDTH && x < MapTile[y].size(); x++) {
			for (int i = 0; i < MapObj[y][x].size(); i++)
				if (MapObj[y][x][i] != -1)
					actObj.push_back(objects.at(MapObj[y][x][i]));
		}
	}
	//actObj.push_back(&trigg);
}
void CPlayScene::UpdateObj(CGameObject* obj, DWORD dt) {
	vector<LPGAMEOBJECT>* _coObj = new vector<LPGAMEOBJECT>();

	float cx, cy;
	player->GetPosition(cx, cy);

	float x, y;

	obj->GetPosition(x, y);

	UpdateActObj(Point(x, y));

	quadtree = CreateQuadtree(actObj, Point(x, y));

	quadtree->Retrieve(_coObj, obj);

	//if (obj->type != g_star)
	_coObj->push_back(player);
	//_coObj->push_back(cannon);
	//coObj->push_back(boom);
	//_coObj->push_back(star);
	/*Map::GetInstance()->updateMap(cx, cy, tf, br);
	Map::GetInstance()->updateMapObject(_coObj);*/

	obj->Update(dt, _coObj);

	quadtree->~Quadtree();
}
void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MAINOBJECT:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MAINOBJECT object was created before!\n");
			return;
		}
		obj = new CMainObject(x,y); 
		player = (CMainObject*)obj;  

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); DebugOut(L"[INFO] brick object created!\n"); break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	DebugOut(L"Ani set is: %d \n", ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	//vector<LPGAMEOBJECT> coObjects;
	DebugOut(L"Update function\n");
	float cx, cy;
	coObj->clear();
	player->GetPosition(cx, cy);

	UpdateActObj(Point(cx, cy));
	quadtree = CreateQuadtree(actObj, Point(cx, cy));

	quadtree->Retrieve(coObj, player);

	player->GetPosition(cx, cy);
	coObj->push_back(player);
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObj->push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, coObj);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	//float cx, cy;

	player->Update(dt, coObj);
	player->GetPosition(cx, cy);

	CGame::GetInstance()->SetCamPos(player);
}

void CPlayScene::Render()
{
	DebugOut(L"coObject len: %d", coObj->size());
	for (int i = 0; i < coObj->size(); i++) {
		//coObj->at(i)->RenderBoundingBox();
		try
		{
			coObj->at(i)->Render();
		}
		catch (exception e)
		{
			DebugOut(L"Render function\n", e);
		}
	};
	DebugOut(L"Render function\n");
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMainObject *mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MAINOBJECT_STATE_JUMP);
		break;
	case DIK_A: 
		//mario->Reset();
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMainObject *mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MAINOBJECT_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MAINOBJECT_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MAINOBJECT_STATE_WALKING_LEFT);
	else
		mario->SetState(MAINOBJECT_STATE_IDLE);
}
