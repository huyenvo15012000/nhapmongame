#pragma once
#include <list>
#include "GameObject.h"

class QuadTree
{
	QNode* root;
};

class QNode
{
	QNode* tl, * tr, * bl, * br;
	int nodeID;
	list<CTreeObject> objects;
};

class CTreeObject
{
	int x1, y1, x2, y2;
	CGameObject* target;
};

