#pragma once
#include "olcFramework.h"
#include "camera.h"

class Weapon
{
protected:
	olc::vf2d m_position;
	olc::vf2d m_direction;

public:
	Weapon(olc::vf2d position, olc::vf2d direction) : 
		m_position(position), 
		m_direction(direction)
	{

	}

	virtual void fire() = 0;
	virtual void update(float fElapsedTime, olc::vf2d position, olc::vf2d direction) = 0;
	virtual ~Weapon() = 0 {};
	virtual void draw_self(Camera * camera) = 0;
};


enum class WeaponState
{
	ready,
	reloading
};


class WeaponAK47 : public Weapon
{

	std::chrono::time_point< std::chrono::system_clock> previous_shoot;
	std::chrono::milliseconds time_to_reload = std::chrono::milliseconds(500);
	WeaponState weapon_state = WeaponState::ready;
public:
	
	WeaponAK47(olc::vf2d position, olc::vf2d direction) : Weapon(position, direction)
	{

	}
	void fire() override;
	void update(float fElapsedTime, olc::vf2d position, olc::vf2d direction) override;
	void draw_self(Camera* camera) override;

	~WeaponAK47() override {};
};
