#include "camera.h"
#include <random>

Camera::Camera(olc::PixelGameEngine* pge) :	
	m_pge(pge)
{
	m_virtual_camera_shape = std::make_shared<RectangleShape>(
		olc::vi2d(0, 0),
		olc::vi2d(m_pge->ScreenWidth(), m_pge->ScreenHeight()),
		olc::BLUE);
}

olc::PixelGameEngine* Camera::get_pge()
{
	return m_pge;
}

void Camera::bind_camera_to_obj(std::shared_ptr<Game_object> obj_to_bind)
{
	m_obj_to_bind = obj_to_bind;
}

void Camera::center_camera_on_obj()
{
	auto new_pos = m_obj_to_bind->get_world_coordinates() - m_virtual_camera_shape->get_size() / 2;
	m_virtual_camera_shape->set_pos(new_pos);
}

bool Camera::is_object_in_camera(std::shared_ptr<Game_object> obj)
{
	return obj->get_shape()->is_there_collision(*m_virtual_camera_shape);
}

olc::vf2d Camera::scale_to_world_coordinates(olc::vf2d screeen_coord)
{
	// for now there is no ratio or scale, just 1:1 translation
	return screeen_coord + m_virtual_camera_shape->get_position();
}

olc::vf2d Camera::scale_to_screen_coordinates(olc::vf2d world_coordinates)
{
	// for now there is no ratio or scale, just 1:1 translation
	return world_coordinates - m_virtual_camera_shape->get_position();
}

olc::vf2d Camera::GetMouseWorldPos()
{
	return scale_to_world_coordinates(m_pge->GetMousePos());
}

void Camera::draw(std::vector<std::shared_ptr<Game_object>> v_game_objects)
{
	draw_background();
	for (auto& game_obj : v_game_objects)
	{
		if (is_object_in_camera(game_obj))
		{
			game_obj->draw_self(static_cast<void*>(this));
		}
	}
}

int get_pattern_offset(int x)
{
	return x - x % 16;
}
void Camera::draw_background()
{
	m_pge->Clear(olc::Pixel(0xC9C9C9C9));
	auto screeen_pos = m_virtual_camera_shape->get_position();

	for (float x = (float)get_pattern_offset(static_cast<int>( screeen_pos.x)); 
			   x < screeen_pos.x + m_virtual_camera_shape->get_size().x ; 
			   x+=16)
		for (float y = (float)get_pattern_offset(static_cast<int>(screeen_pos.y)); 
			       y < screeen_pos.y + m_virtual_camera_shape->get_size().x;
			       y+=16)
		{
			m_pge->FillRect(scale_to_screen_coordinates(olc::vf2d(x, y)), olc::vf2d(2, 2), olc::Pixel(0x694CF7FF));
		}
}

void Camera::update()
{
	center_camera_on_obj();
}

