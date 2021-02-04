#include "Player.h"


Player::Player(olc::vf2d world_coordinates) : Game_object(world_coordinates)
{
	m_shape = std::make_shared<CircleMovableShape>(
		world_coordinates,
		olc::vf2d(16, 16),
		olc::YELLOW);
	sprite = std::make_shared<olc::Renderable>();
	sprite->Load("./Data/blocks.png");

	m_current_weapon = std::make_shared<WeaponAK47>(get_center_of_player(), olc::vf2d(0,0));
}

olc::vf2d Player::get_center_of_player()
{
	return m_world_coordinates + m_shape->get_size() / 2;
}

olc::vf2d Player::get_view_direction()
{
	return m_view_direction;
}

void Player::update(
	float time_delta, 
	std::shared_ptr<Camera> camera,
	std::vector<std::shared_ptr<Game_object>>& v_game_objects)
{
	olc::PixelGameEngine* pge = camera->get_pge();
	olc::vf2d run_direction{ 0,0 };
	olc::vf2d distance{ 0,0 };

	// 1. check if we need to move Player
	if (pge->GetKey(olc::W).bHeld) run_direction.y -= 1;
	if (pge->GetKey(olc::S).bHeld) run_direction.y += 1;
	if (pge->GetKey(olc::A).bHeld) run_direction.x -= 1;
	if (pge->GetKey(olc::D).bHeld) run_direction.x += 1;
	if (run_direction != olc::vf2d{ 0,0 })
	{
		m_run_direction = run_direction.norm();
		distance = m_run_direction * m_f_player_speed * time_delta;
		m_world_coordinates += distance;
		m_shape->set_pos(m_world_coordinates);
	}

	// 2. Update the view direction
	m_view_direction = camera->GetMouseWorldPos() - get_center_of_player();

	// 3. check if there are collisions with player
	for (auto& p_game_obj : v_game_objects)
	{
		auto other_shape = p_game_obj->get_shape();
		if (m_shape->is_there_collision(*other_shape))
		{
			olc::vd2d v_fix = other_shape->get_collizion_fix_vector(*m_shape);
			m_world_coordinates += v_fix;
			m_shape->set_pos(m_world_coordinates);
		}
	}

	// 4. update weapon
	m_current_weapon->update(time_delta, get_center_of_player(), m_view_direction);

	// 5. use weapon
	if (pge->GetMouse(0).bHeld)
	{
		m_current_weapon->fire();
	}

}

void Player::update_position(float time_delta, std::shared_ptr<Camera> camera, std::vector<std::shared_ptr<Game_object>>& v_game_objects)
{

}

void Player::draw_self(void * pCamera)
{
	Camera* camera = (Camera*)pCamera;
	m_current_weapon->draw_self(camera);
	m_shape->draw_self(camera->get_pge(), camera->scale_to_screen_coordinates(m_world_coordinates));
	//camera->get_pge()->DrawString(olc::vi2d(10, 10), m_world_coordinates.str());
}

