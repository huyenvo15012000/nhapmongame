#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"
#include "Rect.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BRICK_WIDTH	8
#define BRICK_HEIGHT	8

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

enum Style {
	normal_brick, sophia, jason
};
struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	float x; 
	float y;
	float yWorld;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int width;
	int height;

	int nx;	 
	int ny;
	bool enable = true;

	bool penetrable;


	int maxx, maxy, minx, miny;

	int state;

	DWORD dt; 

	LPANIMATION_SET animation_set;

	Style type;

public: 
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; this->yWorld = 496 - y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetGamePosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetRealPosition(float& x, float& y) { x = this->x; y = this->yWorld; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetPenetrable(bool b) { this->penetrable = b; }
	bool GetPenetrable() { return this->penetrable; }
	void SetWidthHeight(int w, int h) { this->width = w; this->height = h; }
	int GetState() { return this->state; }


	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	vector<LPCOLLISIONEVENT> SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	CGameObject();

	virtual void RenderBoundingBox();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual Rect GetBoundingBox() = 0;
	void SetStyle(Style style) { this->type = style; }
	Style getType() { return this->type; }

	~CGameObject();
};

