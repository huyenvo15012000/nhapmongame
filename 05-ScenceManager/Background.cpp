#include "Background.h"

void Background::Render()
{
	animation_set->at(0)->Render(x, yWorld);
}

void Background::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}