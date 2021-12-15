#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Gun.h"
#include "Wheel.h"
#include "Connector.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Enemy8.h"
#include "Enemy9.h"
#include "Enemy10.h"
#include "Brick2.h"
#include "Background.h"
#include "Bullet.h"
#include "Portal.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
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
#define OBJECT_TYPE_BRICK2	1001
#define OBJECT_TYPE_GUN	2
#define OBJECT_TYPE_CONNECTOR	3
#define OBJECT_TYPE_WHEEL	4
#define OBJECT_TYPE_ENEMY1	5
#define OBJECT_TYPE_ENEMY2	6
#define OBJECT_TYPE_ENEMY3	7
#define OBJECT_TYPE_ENEMY4	8
#define OBJECT_TYPE_ENEMY5	9
#define OBJECT_TYPE_ENEMY6	10
#define OBJECT_TYPE_ENEMY7	11
#define OBJECT_TYPE_ENEMY8	12
#define OBJECT_TYPE_ENEMY9	13
#define OBJECT_TYPE_ENEMY10	14
#define OBJECT_TYPE_BACKGROUND	20
#define OBJECT_TYPE_BULLET	21
#define OBJECT_TYPE_JASON	1000
#define OBJECT_TYPE_PORTAL	100

#define MAX_SCENE_LINE 1024

vector<LPGAMEOBJECT>* coObj = new vector<LPGAMEOBJECT>();
Background* background;

LPDIRECT3DTEXTURE9 texMap1;
int lx, ly;
int Stage;
Quadtree* quadtree;
Gun* gun;
Connector* connector;
Wheel* wheel;
int main_previous_state = 0;
Quadtree* CPlayScene::CreateQuadtree(vector<LPGAMEOBJECT> entity_list)
{
	Quadtree* quadtree = new Quadtree(1, new Rect(0, 0, 2016, 2016));
	for (auto i = entity_list.begin(); i != entity_list.end(); i++)
	{
		quadtree->Insert(*i);
	}
	return quadtree;
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
		int frame_time = atoi(tokens[i + 1].c_str());
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

	CAnimations* animations = CAnimations::GetInstance();

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

	if (tokens.size() < 3)		
		return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;
	switch (object_type)
	{
	case OBJECT_TYPE_MAINOBJECT:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MAINOBJECT object was created before!\n");
			return;
		}
		obj = new CMainObject(x, y);
		player = (CMainObject*)obj;
		if (main_previous_state != 0)
			player->SetState(main_previous_state);
		break;
	case OBJECT_TYPE_JASON:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MAINOBJECT object was created before!\n");
			return;
		}
		DebugOut(L"Jason crea");
		obj = new CMainObject(x, y);
		player = (CMainObject*)obj;
		player->SetJason();
		if (main_previous_state != 0)
			player->SetState(main_previous_state);
		break;
	case OBJECT_TYPE_BACKGROUND:
		obj = new Background();
		background = (Background*)obj;
		DebugOut(L"BG creaet \n");
		break;
	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		break;
	case OBJECT_TYPE_BRICK2:
		obj = new Brick2();
		break;
	case OBJECT_TYPE_GUN:
		obj = new Gun();
		player->addGun((Gun*)obj);
		break;
	case OBJECT_TYPE_CONNECTOR:
		obj = new Connector();
		player->addConnector((Connector*)obj); break;
	case OBJECT_TYPE_WHEEL:
		obj = new Wheel();
		player->addWheel((Wheel*)obj); break;
	case OBJECT_TYPE_ENEMY1:
		obj = new Enemy1();
		break;
	case OBJECT_TYPE_ENEMY2:
		obj = new Enemy2();
		obj->SetState(ENEMY2_STATE_WALKING);
		break;
	case OBJECT_TYPE_ENEMY3:
		obj = new Enemy3();
		break;
	case OBJECT_TYPE_ENEMY4:
		obj = new Enemy4();
		break;
	case OBJECT_TYPE_ENEMY5:
		obj = new Enemy5();
		break;
	case OBJECT_TYPE_ENEMY6:
		obj = new Enemy6();
		break;
	case OBJECT_TYPE_ENEMY7:
		obj = new Enemy7();
		break;
	case OBJECT_TYPE_ENEMY8:
		obj = new Enemy8();
		break;
	case OBJECT_TYPE_ENEMY9:
		obj = new Enemy9();
		break;
	case OBJECT_TYPE_ENEMY10:
		obj = new Enemy10();
		break;
	case OBJECT_TYPE_BULLET:
		obj = new Bullet(0, 0);
		player->addBullet((Bullet*)obj);
		break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		Stage = scene_id;
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	switch (object_type)
	{
		case OBJECT_TYPE_CONNECTOR:
			break;
		case OBJECT_TYPE_JASON:
			break;
		case OBJECT_TYPE_MAINOBJECT:
			break;
		case OBJECT_TYPE_GUN:
			break;
		case OBJECT_TYPE_WHEEL:
			break;
		case OBJECT_TYPE_BULLET:
			break;
		case OBJECT_TYPE_BACKGROUND:
			break;
		default:
			objects.push_back(obj);
			break;
	}
	//objects.push_back(obj);
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
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
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
	coObj->clear();
	quadtree = CreateQuadtree(objects);
	quadtree->Retrieve(coObj, player);
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 6; i < coObj->size(); i++)
	{
		if (coObj->at(i)->IsEnable())
			coObj->at(i)->Update(dt, coObj);
		else
			coObj->erase(coObj->begin() + i);
	}

	if (player == NULL) return;

	player->Update(dt, coObj);
	CGame::GetInstance()->SetCamPos(player);
	quadtree->~Quadtree();
}

void CPlayScene::Render()
{
	if (background)
		background->Render();
	if (player)
		player->Render();
	for (int i = 0; i < coObj->size(); i++)
		if (coObj->at(i)->IsEnable())
			coObj->at(i)->Render();
		else
			coObj->erase(coObj->begin() + i);
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	/*if (player != NULL)
		main_previous_state = player->GetState();*/
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Disable();

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMainObject* main = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_A:		
		main->Fire();
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMainObject* main = ((CPlayScene*)scence)->GetPlayer();
	main->SetState(MAINOBJECT_STATE_STOP);
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMainObject* main = ((CPlayScene*)scence)->GetPlayer();
	// disable control key when Mario die 
	if (main->GetState() == MAINOBJECT_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		main->SetState(MAINOBJECT_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		main->SetState(MAINOBJECT_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_UP))
		main->SetState(MAINOBJECT_STATE_WALKING_UP);
	else if (game->IsKeyDown(DIK_DOWN))
		main->SetState(MAINOBJECT_STATE_WALKING_DOWN);
	else if (game->IsKeyDown(DIK_SPACE))
		main->SetState(MAINOBJECT_STATE_JUMP);
	else if (game->IsKeyDown(DIK_W))
		main->SetState(MAINOBJECT_STATE_FIRE_UP);
	else
		main->SetState(MAINOBJECT_STATE_IDLE);
}