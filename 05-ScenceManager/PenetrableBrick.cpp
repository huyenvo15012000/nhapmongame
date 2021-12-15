#include "PenetrableBrick.h"
void PenetrableBrick::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void PenetrableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}