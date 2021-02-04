#pragma once
#include <memory>
#include "olcFramework.h"
#include "shape.h"
#include <cassert>


class Game_object : public std::enable_shared_from_this<Game_object>
{
protected:
	olc::vf2d m_world_coordinates;
	std::shared_ptr<Shape> m_shape = nullptr;
public:
	Game_object(olc::vf2d world_coordinates) :
		m_world_coordinates(world_coordinates)
	{}
	virtual void draw_self(void *) = 0;

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