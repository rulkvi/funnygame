#pragma once
#include "olcFramework.h"
#include "shape.h"
#include <cassert>
#include "world.h"

class Game_object;

class Camera
{
	std::shared_ptr<Game_object> m_obj_to_bind = nullptr;
	olc::PixelGameEngine* m_pge = nullptr;
	std::shared_ptr<Shape> m_virtual_camera_shape = nullptr;
public:
	Camera(olc::PixelGameEngine* pge, std::shared_ptr<Game_object> obj_to_bind);

	olc::PixelGameEngine* get_pge();

	void center_camera_on_obj();

	bool is_object_in_camera(std::shared_ptr<Game_object> obj);

	olc::vd2d scale_to_world_coordinates(olc::vd2d screeen_coord);

	olc::vd2d scale_to_screen_coordinates(olc::vd2d world_coordinates);

	olc::vd2d GetMouseWorldPos();

	void draw(std::vector<std::shared_ptr<Game_object>> v_game_objects);
	
	void draw_background();

	void update();
};


