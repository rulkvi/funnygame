#pragma once
#include "camera.h"

class Drawable
{
public:
	virtual void draw_self(Camera&) = 0;
};