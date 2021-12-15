#pragma once
#include "GameObject.h"
#include "Rect.h"

#define MAX_LEVEL               25
#define MAX_OBJECT_IN_REGION    800

class Quadtree
    {
    private:
        int            m_level;
        Rect* m_region;
        vector<LPGAMEOBJECT>* m_objects_list;
        Quadtree** m_nodes;

        bool           IsContain(LPGAMEOBJECT entity);
        void           Split();
    public:
        Quadtree();
        Quadtree(int level, Rect* region);
        int count() { return m_objects_list->size(); }
        void           Clear();
        void           Insert(LPGAMEOBJECT entity);
        void Retrieve(vector<LPGAMEOBJECT>* return_objects_list, LPGAMEOBJECT entity);
};

