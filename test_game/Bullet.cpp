#include "Bullet.h"

Bullet::Bullet(olc::vf2d world_coordinates, olc::vf2d direction, float speed) :
	Game_object(world_coordinates),
	m_direction(direction.norm()),
	m_speed(speed)
{
	m_shape = std::make_shared<CircleMovableShape>(
		world_coordinates,
		olc::vf2d(4, 4),
		olc::VERY_DARK_MAGENTA);
}

bool Bullet::update(float fElapsedTime, std::vector<std::shared_ptr<Game_object>>& v_game_objects, std::shared_ptr<Camera> camera)
{
	m_world_coordinates += m_direction * m_speed * fElapsedTime;
	m_shape->set_pos(m_world_coordinates);

	if (!camera->is_object_in_camera(shared_from_this()))
	{
		return false;
	}

	for (auto& game_obj : v_game_objects)
	{
		if (m_shape->is_there_collision(*game_obj->get_shape()))
		{

			return false; // returning false here deletes the bullet
		}
	}
	return true;
}

void Bullet::draw_self(void * pCamera)
{
	Camera* camera = (Camera*)pCamera;
	m_shape->draw_self(camera->get_pge(), camera->scale_to_screen_coordinates(m_world_coordinates));
}
