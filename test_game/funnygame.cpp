#include "funnygame.h"
#include "Player.h"
#include "world.h"

bool FunnyGame::OnUserCreate()
{
	// Called once at the start, so create things here
	gfxTiles.Load("./Data/blocks.png");

	
	auto & pWorld = World::instance();
	pCamera = std::make_shared<Camera>(this);
	pWorld.set_camera(pCamera);

	return true;
}

bool FunnyGame::OnUserUpdate(float fElapsedTime)
{
	// handle of debug.
	std::chrono::duration<float> dElapsedTime(fElapsedTime);
	if (dElapsedTime > 1s)
	{
		dElapsedTime = target_time_per_frame;
		fElapsedTime = target_time_per_frame.count();
	}


	// GRAPHICS

	SetPixelMode(olc::Pixel::NORMAL);
	auto& pWorld = World::instance();
	pWorld.update_player(fElapsedTime);
	pWorld.update_bullets(fElapsedTime);
	pWorld.draw_camera();
	pWorld.draw_bullets();


	if (fElapsedTime < target_time_per_frame.count())
	{
		auto dur_to_sleep = target_time_per_frame - dElapsedTime;
		std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(dur_to_sleep));
	}

	return true;
}
