#include "camera.h"

Camera::Camera(olc::PixelGameEngine* pge, std::shared_ptr<Game_object> obj_to_bind) :
	m_obj_to_bind(obj_to_bind),
	m_pge(pge)
{
	m_virtual_camera_shape = std::make_shared<RectangleShape>(
		olc::vi2d(0, 0),
		olc::vi2d(m_pge->ScreenWidth(), m_pge->ScreenHeight()),
		olc::BLUE);
	center_camera_on_obj();
}

olc::PixelGameEngine* Camera::get_pge()
{
	return m_pge;
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

olc::vd2d Camera::scale_to_world_coordinates(olc::vd2d screeen_coord)
{
	// for now there is no ratio or scale, just 1:1 translation
	return screeen_coord + m_virtual_camera_shape->get_position();
}

olc::vd2d Camera::scale_to_screen_coordinates(olc::vd2d world_coordinates)
{
	// for now there is no ratio or scale, just 1:1 translation
	return world_coordinates - m_virtual_camera_shape->get_position();
}

olc::vd2d Camera::GetMouseWorldPos()
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
			game_obj->draw_self(*this);
		}
	}
	m_pge->DrawRect(scale_to_screen_coordinates(m_virtual_camera_shape->get_position()), m_virtual_camera_shape->get_size(), olc::CYAN);
}

int get_pattern_offset(int x)
{
	return x - x % 32;
}
void Camera::draw_background()
{
	m_pge->Clear(olc::GREEN);
	auto screeen_pos = m_virtual_camera_shape->get_position();

	for (int x = get_pattern_offset(screeen_pos.x); x < screeen_pos.x + m_virtual_camera_shape->get_size().x ; x+=32)
		for (int y = get_pattern_offset(screeen_pos.y); y < screeen_pos.y + m_virtual_camera_shape->get_size().x; y+=32)
		{
			m_pge->DrawRect(scale_to_screen_coordinates(olc::vi2d(x, y)), olc::vi2d(4, 4), olc::DARK_GREEN);
		}
}

void Camera::update()
{
	center_camera_on_obj();
}

