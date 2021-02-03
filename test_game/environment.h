#pragma once
#include "world.h"

class Environment_obj : public Game_object
{
	std::shared_ptr<olc::Renderable> sprite = nullptr;
	int skin_idx = 0;
public:
	Environment_obj(olc::vi2d world_coordinates) : Game_object(world_coordinates)
	{
		sprite = std::make_shared<olc::Renderable>();
		sprite->Load("./Data/objects.png");
		skin_idx = 2;
	}

	void set_shape(std::shared_ptr<Shape> shape)
	{
		m_shape = shape;
	}

	void update(float fElapsedTime)
	{
		
	}

	void draw_self(Camera& camera) override
	{
		m_shape->draw_self(camera.get_pge(), camera.scale_to_screen_coordinates(m_world_coordinates), *sprite, skin_idx);
	}
};