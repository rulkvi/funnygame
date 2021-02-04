#pragma once
#include "world.h"

class Environment_obj : public Game_object
{
	std::shared_ptr<olc::Renderable> sprite = nullptr;
	int skin_idx = 0;
public:
	Environment_obj(std::shared_ptr<Shape> shape) : Game_object(shape->get_position())
	{
		m_shape = shape;
		sprite = std::make_shared<olc::Renderable>();
		sprite->Load("./Data/objects.png");
		skin_idx = 2;
	}

	void update(float fElapsedTime)
	{
		
	}

	void draw_self(void * pCamera) override
	{
		Camera* camera = (Camera*)(pCamera);
		m_shape->draw_self(camera->get_pge(), camera->scale_to_screen_coordinates(m_world_coordinates)); // , * sprite, skin_idx);
	}
};