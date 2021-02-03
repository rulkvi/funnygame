#pragma once
#include "olcFramework.h"
#include "shape.h"
#include <cassert>
#include "camera.h"

class Camera;

class Game_object
{
protected:
	olc::vf2d m_world_coordinates;
	std::shared_ptr<Shape> m_shape = nullptr;
public:
	Game_object(olc::vi2d world_coordinates):
		m_world_coordinates(world_coordinates)
	{}

	virtual void draw_self(Camera& camera) = 0;

	olc::vf2d get_world_coordinates()
	{
		return m_world_coordinates;
	}
	std::shared_ptr<Shape> get_shape()
	{
		assert(m_shape != nullptr);

		return m_shape;
	}
};

class Weapon
{
	
public:
	Weapon()
	{
		
	}

	void draw_self(olc::PixelGameEngine* pge, olc::vi2d players_coords)
	{
		auto mouse_pos = pge->GetMousePos();
		pge->DrawLine(mouse_pos, players_coords, olc::DARK_BLUE, 0xf0f0f0f0);
	}
};



class World
{

};
