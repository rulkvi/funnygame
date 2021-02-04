#pragma once
#include "olcFramework.h"
#include "camera.h"
#include "GameObject.h"



class Bullet : public Game_object
{
	olc::vf2d m_direction;
	float m_speed;
public:
	Bullet(olc::vf2d world_coordinates, olc::vf2d direction, float speed);

	bool update(float fElapsedTime, std::vector<std::shared_ptr<Game_object>>& v_game_objects, std::shared_ptr<Camera> camera);

	void draw_self(void * camera) override;
};

