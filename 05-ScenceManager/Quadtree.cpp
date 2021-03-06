#include "Quadtree.h"
#include "MainObject.h"
void Quadtree::Clear()
{
    // Clear all nodes
    if (m_nodes)
    {
        for (int i = 0; i < 4; i++)
        {
            m_nodes[i]->Clear();
            delete m_nodes[i];
        }
        delete[] m_nodes;
    }

    // Clear current Quadtree
    m_objects_list->clear();

    delete m_objects_list;
    delete m_region;
}

bool Quadtree::IsContain(LPGAMEOBJECT entity)
{
    float l, t, r, b, x, y, w, h;
    entity->GetBoundingBox(l, t, r, b);
    x = l;
    y = t;
    if (dynamic_cast<CMainObject*>(entity))
    {
        w = r - l + 250;
        h = b - t + 250;
    }
    else
    {
        w = r - l;
        h = b - t;
    }
    return !(l + w < m_region->x ||
        y + h < m_region->y ||
        x > m_region->x + m_region->getWidth() ||
        y > m_region->y + m_region->getHeight());
}

void Quadtree::Split()
{
    m_nodes = new Quadtree * [4];

    m_nodes[0] = new Quadtree(m_level + 1,
        new Rect(m_region->x, m_region->y, m_region->getWidth() / 2, m_region->getHeight() / 2));
    m_nodes[1] = new Quadtree(m_level + 1,
        new Rect(m_region->x + m_region->getWidth() / 2, m_region->y, m_region->getWidth() / 2, m_region->getHeight() / 2));
    m_nodes[2] = new Quadtree(m_level + 1,
        new Rect(m_region->x, m_region->y + m_region->getHeight() / 2, m_region->getWidth() / 2, m_region->getHeight() / 2));
    m_nodes[3] = new Quadtree(m_level + 1,
        new Rect(m_region->x + m_region->getWidth() / 2,
            m_region->y + m_region->getHeight() / 2, m_region->getWidth() / 2, m_region->getHeight() / 2));
}

Quadtree::Quadtree(int level, Rect* region)
{
    m_level = level;
    m_region = region;
    m_objects_list = new vector<LPGAMEOBJECT>();
}

void Quadtree::Insert(LPGAMEOBJECT entity)
{
    // Insert entity into corresponding nodes
    if (m_nodes)
    {
        if (m_nodes[0]->IsContain(entity))
            m_nodes[0]->Insert(entity);
        if (m_nodes[1]->IsContain(entity))
            m_nodes[1]->Insert(entity);
        if (m_nodes[2]->IsContain(entity))
            m_nodes[2]->Insert(entity);
        if (m_nodes[3]->IsContain(entity))
            m_nodes[3]->Insert(entity);

        return; // Return here to ignore rest.
    }

    // Insert entity into current quadtree
    if (this->IsContain(entity))
        m_objects_list->push_back(entity);

    // Split and move all objects in list into it?s corresponding nodes
    if (m_objects_list->size() > MAX_OBJECT_IN_REGION && m_level < MAX_LEVEL)
    {
        Split();

        while (!m_objects_list->empty())
        {
            if (m_nodes[0]->IsContain(m_objects_list->back()))
                m_nodes[0]->Insert(m_objects_list->back());
            if (m_nodes[1]->IsContain(m_objects_list->back()))
                m_nodes[1]->Insert(m_objects_list->back());
            if (m_nodes[2]->IsContain(m_objects_list->back()))
                m_nodes[2]->Insert(m_objects_list->back());
            if (m_nodes[3]->IsContain(m_objects_list->back()))
                m_nodes[3]->Insert(m_objects_list->back());

            m_objects_list->pop_back();
        }
    }
}

void Quadtree::Retrieve(vector<LPGAMEOBJECT>* return_objects_list, LPGAMEOBJECT entity)
{
    if (m_nodes)
    {
        if (m_nodes[0]->IsContain(entity))
            m_nodes[0]->Retrieve(return_objects_list, entity);
        if (m_nodes[1]->IsContain(entity))
            m_nodes[1]->Retrieve(return_objects_list, entity);
        if (m_nodes[2]->IsContain(entity))
            m_nodes[2]->Retrieve(return_objects_list, entity);
        if (m_nodes[3]->IsContain(entity))
            m_nodes[3]->Retrieve(return_objects_list, entity);

        return; // Return here to ignore rest.
    }

    // Add all entities in current region into return_objects_list
    if (this->IsContain(entity))
    {
        for (auto i = m_objects_list->begin(); i != m_objects_list->end(); i++)
        {
            if (entity != *i)
                return_objects_list->push_back(*i);
        }
    }
}
