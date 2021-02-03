#include "Player.h"


Player::Player(olc::vi2d world_coordinates) : Game_object(world_coordinates)
{
	m_shape = std::make_shared<MovableShape>(
		world_coordinates,
		olc::vi2d(16, 16),
		olc::YELLOW);
	sprite = std::make_shared<olc::Renderable>();
	sprite->Load("./Data/blocks.png");
	m_current_weapon = std::make_shared<Weapon>();
}

olc::vi2d Player::get_center_of_player()
{
	return m_world_coordinates + m_shape->get_size() / 2;
}

void Player::update(float time_delta, olc::PixelGameEngine* pge)
{
	olc::vf2d run_direction{ 0,0 };
	if (pge->GetKey(olc::W).bHeld) run_direction.y -= 1;
	if (pge->GetKey(olc::S).bHeld) run_direction.y += 1;
	if (pge->GetKey(olc::A).bHeld) run_direction.x -= 1;
	if (pge->GetKey(olc::D).bHeld) run_direction.x += 1;
	if (run_direction != olc::vf2d{ 0,0 })
	{
		auto norm_direction = run_direction.norm();
		m_world_coordinates += m_f_player_speed * norm_direction * time_delta;
		m_shape->set_pos(m_world_coordinates);
	}

	m_view_direction = pge->GetMousePos() - m_world_coordinates;
}

void Player::draw_self(Camera& camera)
{
	m_current_weapon->draw_self(camera.get_pge(), camera.scale_to_screen_coordinates(get_center_of_player()));
	m_shape->draw_self(camera.get_pge(), camera.scale_to_screen_coordinates(m_world_coordinates), *sprite, 1);

	camera.get_pge()->DrawString(olc::vi2d(10, 10), m_world_coordinates.str());
}

