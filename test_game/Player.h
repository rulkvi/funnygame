#pragma once
#include "world.h"

class Player : public Game_object
{
	std::shared_ptr<olc::Renderable> sprite = nullptr;
	float m_f_player_speed = 200; // pixel per second
	olc::vi2d m_view_direction{ 1,0 };
	std::shared_ptr<Weapon> m_current_weapon = nullptr;

public:
	Player(olc::vi2d world_coordinates);

	olc::vi2d get_center_of_player();

	void update(float time_delta, olc::PixelGameEngine* pge, std::vector<std::shared_ptr<Game_object>>& v_game_objects);

	void draw_self(Camera& camera) override;
};




