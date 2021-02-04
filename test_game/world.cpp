#include "world.h"

void World::add_borders(olc::vi2d border_begin, olc::vi2d border_end)
{
	int border_thickness = 32;
	olc::Pixel border_color = olc::DARK_GREY;
	auto env_shape1 = std::make_shared<RectangleShape>(
		olc::vi2d{ border_begin.x, border_begin.y - border_thickness },
		olc::vi2d(border_end.x - border_begin.x, border_thickness),
		border_color);

	auto env_shape2 = std::make_shared<RectangleShape>(
		olc::vi2d{ border_begin.x - border_thickness, border_begin.y - border_thickness },
		olc::vi2d(border_thickness, border_end.y + 2 * border_thickness - border_begin.y),
		border_color);
	
	auto env_shape3 = std::make_shared<RectangleShape>(
		olc::vi2d{ border_begin.x , border_end.y },
		olc::vi2d(border_end.x - border_begin.x, border_thickness),
		border_color);

	auto env_shape4 = std::make_shared<RectangleShape>(
		olc::vi2d{ border_end.x, border_begin.y - border_thickness },
		olc::vi2d(border_thickness, border_end.y + 2 * border_thickness - border_begin.y),
		border_color);

	m_vector_of_env_objects.emplace_back(std::make_shared<Environment_obj>(env_shape1));
	m_vector_of_env_objects.emplace_back(std::make_shared<Environment_obj>(env_shape2));
	m_vector_of_env_objects.emplace_back(std::make_shared<Environment_obj>(env_shape3));
	m_vector_of_env_objects.emplace_back(std::make_shared<Environment_obj>(env_shape4));
}

void World::add_environment(olc::vi2d border_begin, olc::vi2d border_end)
{
	int border_thickness = 32;
	olc::Pixel border_color = olc::DARK_GREY;
	olc::vi2d env_begin{ 120, 120 };

	for (int x = 1; x < 5; x ++)
		for (int y = 1; y < 5; y++)
	{
		auto env_shape1 = std::make_shared<RectangleShape>(
			olc::vi2d { 120*x, 120*y },
			olc::vi2d(64, 64),
			border_color);
		m_vector_of_env_objects.emplace_back(std::make_shared<Environment_obj>(env_shape1));
	}
}

void World::add_player(olc::vf2d starting_pos)
{
	m_player = std::make_shared<Player>(starting_pos);
	m_vector_of_env_objects.push_back(m_player); // player also can collide with bullets and etc.
}

void World::set_camera(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
	m_camera->bind_camera_to_obj(m_player);
}

std::shared_ptr<Camera> World::get_camera()
{
	return m_camera;
}

void World::add_bullet(std::shared_ptr<Bullet> bullet)
{
	m_vector_of_bullets.push_back(bullet);
}

void World::remove_bullet(std::shared_ptr<Bullet> bullet)
{
	m_vector_of_bullets.remove(bullet);
}

void World::update_bullets(float fElapsedTime)
{
	auto bullet_iterator = m_vector_of_bullets.begin();
	while (bullet_iterator != m_vector_of_bullets.end())
	{
		if (!(*bullet_iterator)->update(fElapsedTime, m_vector_of_env_objects, m_camera))
		{
			m_vector_of_bullets.erase(bullet_iterator++);
		}
		else
		{
			++bullet_iterator;
		}
	}
}

void World::update_player(float fElapsedTime)
{
	m_player->update(fElapsedTime, m_camera, m_vector_of_env_objects);
	m_camera->update();
}

void World::draw_camera()
{
	m_camera->draw(m_vector_of_env_objects);
}

void World::draw_bullets()
{
	for (auto& bullet : m_vector_of_bullets)
	{
		bullet->draw_self(m_camera.get());
	}
}

void World::draw_environment()
{
	for (auto& obj : m_vector_of_env_objects)
	{
		obj->draw_self(m_camera.get());
	}
}
