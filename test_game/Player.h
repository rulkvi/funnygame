#pragma once
#include "camera.h"
#include "Weapon.h"
#include "GameObject.h"



class Player : public Game_object
{
	std::shared_ptr<olc::Renderable> sprite = nullptr;
	float m_f_player_speed = 60; // pixel per second
	olc::vf2d m_view_direction{ 1,0 };
	olc::vf2d m_run_direction{ 1,0 };
	std::shared_ptr<Weapon> m_current_weapon = nullptr;

public:
	Player(olc::vf2d world_coordinates);

	olc::vf2d get_center_of_player();
	olc::vf2d get_view_direction();

	void update(
		float time_delta, 
		std::shared_ptr<Camera> camera,
		std::vector<std::shared_ptr<Game_object>>& v_game_objects);

	void update_position(
		float time_delta,
		std::shared_ptr<Camera> camera,
		std::vector<std::shared_ptr<Game_object>>& v_game_objects);

	void draw_self(void *) override;


};




