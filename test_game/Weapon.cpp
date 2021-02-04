#include "Weapon.h"
#include "Bullet.h"
#include "world.h"
#include "camera.h"

void WeaponAK47::draw_self(Camera* camera)
{
	auto begin_pos = camera->scale_to_screen_coordinates(m_position);
	auto direction = begin_pos + m_direction;
	auto direction_short = begin_pos + (m_direction).norm() * 16;

	camera->get_pge()->DrawLine(begin_pos, direction, olc::RED, 0xffffffff);
	camera->get_pge()->DrawLine(begin_pos, direction_short, olc::BLACK, 0xffffffff);
}

void WeaponAK47::fire()
{
	if (weapon_state == WeaponState::ready)
	{
		previous_shoot = std::chrono::system_clock::now();
		weapon_state = WeaponState::reloading;
		auto direction = m_direction.norm() * 20;
		auto pBullet = std::make_shared<Bullet>(m_position + direction, m_direction, (float)120);
		auto & pWorld = World::instance();
		pWorld.add_bullet(pBullet);
	}
}

void WeaponAK47::update(float fElapsedTime, olc::vf2d position, olc::vf2d direction)
{
	m_position = position;
	m_direction = direction;
	auto t_now = std::chrono::system_clock::now();
	if (weapon_state == WeaponState::reloading)
	{
		if (std::chrono::system_clock::now() - previous_shoot > time_to_reload)
		{
			weapon_state = WeaponState::ready;
		}
	}
}
