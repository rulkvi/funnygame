#pragma once
#include "olcFramework.h"
#include <optional>
#include <chrono>
#include <thread>

class RectangleShape;

class Shape
{
protected:
	olc::vi2d m_position;
	olc::vi2d m_size;
	olc::Pixel m_color;
public:
	Shape(olc::vi2d position, olc::vi2d size, olc::Pixel color) :
		m_position(position),
		m_size(size),
		m_color(color)
	{

	};

	virtual void draw_self(olc::PixelGameEngine* pge, olc::vi2d draw_position, const olc::Renderable& skin, int skin_idx) = 0;
	virtual void update_pos(olc::vf2d force, float time_delta, std::vector<std::shared_ptr<RectangleShape>>& shapes_to_collide) = 0;
	virtual ~Shape() {};
	virtual void on_collizion(Shape& shape) = 0;
	virtual bool is_point_in_shape(olc::vi2d point) = 0;
	virtual bool is_there_collision(Shape& otherRectangle) = 0;

	olc::vi2d get_position()
	{
		return m_position;
	}

	olc::vi2d get_size()
	{
		return m_size;
	}

	void set_pos(olc::vf2d new_pos)
	{
		m_position = new_pos;
	}
};

class RectangleShape : public Shape
{
	olc::vf2d size{ 16,16 };
public:
	RectangleShape(olc::vi2d position, olc::vi2d size, olc::Pixel color) :Shape(position, size, color)
	{};

	bool is_point_in_shape(olc::vi2d point) override
	{
		if (point.x > m_position.x && 
			point.x < m_position.x + m_size.x && 
			point.y > m_position.y && 
			point.y < m_position.y + m_size.y)
		{
			return true;
		}
		return false;
	}

	void draw_self(olc::PixelGameEngine* pge, olc::vi2d draw_position, const olc::Renderable& skin, int skin_idx) override
	{
		pge->DrawPartialSprite(draw_position, skin.Sprite(), olc::vi2d(skin_idx, 0) * size, size);
	}

	void update_pos(olc::vf2d force, float time_delta, std::vector<std::shared_ptr<RectangleShape>>& shapes_to_collide) override
	{
		return;
	}

	bool is_there_collision(Shape& otherRectangle) override
	{
		auto other_rect_position = otherRectangle.get_position();
		auto other_rect_size = otherRectangle.get_size();
		if (m_position.x < other_rect_position.x + other_rect_size.x &&
			m_position.x + m_size.x > other_rect_position.x &&
			m_position.y < other_rect_position.y + other_rect_size.y &&
			m_position.y + m_size.y > other_rect_position.y) {
			return true;
		}
		else
			return false;
	}

// 	olc::vi2d get_norm_vec_to_collizion(RectangleShape* otherRectangle)
// 	{
// 		
// 	}

	void on_collizion(Shape& shape) override
	{
		m_color += olc::DARK_GREY;
	}


	virtual ~RectangleShape() {};
};


class MovableShape : public RectangleShape
{
private:
	olc::Renderable gfxTiles;
	olc::vf2d size{ 16,16 };
	bool b_collision_exist = false;

public:
	MovableShape(olc::vi2d position, olc::vi2d size, olc::Pixel color) :
		RectangleShape(position, size, color) {};

	void process_collisions(std::vector<std::shared_ptr<RectangleShape>>& shapes_to_collide)
	{
		b_collision_exist = false;
		for (auto& item : shapes_to_collide)
		{
			if (item.get() == this)
				continue;
			if (item->is_there_collision(*this))
			{
				on_collizion(*item.get());
				item->on_collizion(*this);
			}
		}
		if (!b_collision_exist)
		{
			m_color = olc::GREEN;
		}
	}

	

	void update_pos(olc::vf2d direction, float time_delta, std::vector<std::shared_ptr<RectangleShape>>& shapes_to_collide) override
	{
		// for now we don't care about the mass of the objects - lets assume they all are equal
		
		m_position += direction * time_delta;
		process_collisions(shapes_to_collide);
	}

	void on_collizion(Shape& shape) override
	{
		b_collision_exist = true;
		m_color = olc::RED;		 
	}

	void draw_self(olc::PixelGameEngine* pge, olc::vi2d draw_position, const olc::Renderable& skin, int skin_idx) override
	{
		pge->DrawPartialSprite(draw_position, skin.Sprite(), olc::vi2d(skin_idx, 0) * size, size);
	}

	virtual ~MovableShape()
	{

	}
};