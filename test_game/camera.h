#pragma once
#include "olcFramework.h"
#include "shape.h"
#include <cassert>
#include "GameObject.h"


class Camera
{
	std::shared_ptr<Game_object> m_obj_to_bind = nullptr;
	olc::PixelGameEngine* m_pge = nullptr;
	std::shared_ptr<Shape> m_virtual_camera_shape = nullptr;
public:
	Camera(olc::PixelGameEngine* pge);

	olc::PixelGameEngine* get_pge();

	void bind_camera_to_obj(std::shared_ptr<Game_object> obj_to_bind);

	void center_camera_on_obj();

	bool is_object_in_camera(std::shared_ptr<Game_object> obj);

	olc::vf2d scale_to_world_coordinates(olc::vf2d screeen_coord);

	olc::vf2d scale_to_screen_coordinates(olc::vf2d world_coordinates);

	olc::vf2d GetMouseWorldPos();

	void draw(std::vector<std::shared_ptr<Game_object>> v_game_objects);
	
	void draw_background();

	void update();
};


