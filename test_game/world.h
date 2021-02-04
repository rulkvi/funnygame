#pragma once
#include "camera.h"
#include "Bullet.h"
#include "GameObject.h"
#include "singleton.h"
#include "environment.h"
#include "Player.h"

class World final : public Singleton<World>
{
	std::vector<std::shared_ptr<Game_object>> m_vector_of_env_objects;
	std::list<std::shared_ptr<Bullet>> m_vector_of_bullets;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Player> m_player;

	void add_borders(olc::vi2d border_begin, olc::vi2d border_end);

	void add_environment(olc::vi2d border_begin, olc::vi2d border_end);

	void add_player(olc::vf2d starting_pos);
public:
	World(token) {
		add_borders(olc::vi2d(0, 0), olc::vi2d(700, 700));
		add_player(olc::vi2d(50, 50));
		add_environment(olc::vi2d(0, 0), olc::vi2d(700, 700));
	};
	void set_camera(std::shared_ptr<Camera> camera);
	std::shared_ptr<Camera> get_camera();
	void add_bullet(std::shared_ptr<Bullet> bullet);

	void remove_bullet(std::shared_ptr<Bullet> bullet);

	void update_bullets(float fElapsedTime);
	void update_player(float fElapsedTime);

	void draw_camera();
	void draw_bullets();
	void draw_environment();

};

