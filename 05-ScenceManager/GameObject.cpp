#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;
	float _x, _y;
	Rect re = GetBoundingBox();
	_x = re.tf.x;
	_y = re.tf.y;
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 1;
	rect.top = 1;
	rect.right = r - l;
	rect.bottom = b - t;

	CGame::GetInstance()->Draw((int)_x, (int)_y, bbox, rect.left, rect.top, rect.right + 1, rect.bottom + 1, 50);
}
vector<LPCOLLISIONEVENT> CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;
	Style style;
	Rect r;
	r = coO->GetBoundingBox();
	style = coO->getType();
	sl = r.tf.x;
	st = r.tf.y;
	sr = r.br.x;
	sb = r.br.y;

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	r = GetBoundingBox();

	ml = r.tf.x;
	mt = r.tf.y;
	mr = r.br.x;
	mb = r.br.y;
	CGame::SweptAABB(
			ml, mt, mr, mb,
			dx, dy,
			sl, st, sr, sb,
			t, nx, ny, coO->GetPenetrable()
		);

		vector<CCollisionEvent*> e;
		e.push_back(new CCollisionEvent(t, nx, ny, coO));
		return e;

}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		vector<LPCOLLISIONEVENT> e = SweptAABBEx(coObjects->at(i));
		for (UINT j = 0; j < e.size(); j++)
			if (e[j]->t > -1.0f && e[j]->t <= 1.0f)
				coEvents.push_back(e[j]);
			else
				delete e[j];
	}
	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	bool px = true, py = true;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];


		if (c->t >= 0 && !c->obj->penetrable) {
			if (c->t <= min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i;
				px = px && c->obj->penetrable;
			}

			if (c->t <= min_ty && c->ny != 0) {
				min_ty = c->t; ny = c->ny; min_iy = i;
				py = py && c->obj->penetrable;
			}
		}
	}
	if (min_ix >= 0) {
		if (px) {
			min_tx = 1.f;
		}
		coEventsResult.push_back(coEvents[min_ix]);
	}
	if (min_iy >= 0) {
		if (py) {
			min_ty = 1.f;
			ny = 0;
		}
		coEventsResult.push_back(coEvents[min_iy]);
	}
}


CGameObject::~CGameObject()
{

}