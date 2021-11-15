#pragma once
#include <list>
#include "GameObject.h"

class CTreeObject
{
	int x1, y1, x2, y2;
	CGameObject* target;
};

class QNode
{
	QNode* tl, * tr, * bl, * br;
	int nodeID;
	list<CTreeObject> objects;
};

class QuadTree
{
	QNode* root;
protected:
	void build(QNode* n);
	void split();
};



