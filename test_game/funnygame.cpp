#include "funnygame.h"
#include "Player.h"

bool FunnyGame::OnUserCreate()
{
	// Called once at the start, so create things here
	gfxTiles.Load("./Data/blocks.png");
	auto env_shape = std::make_shared<RectangleShape>(
		olc::vi2d(30, 30),
		olc::vi2d(32, 32),
		olc::GREEN);
	pEnvironment = std::make_shared<Environment_obj>(olc::vi2d(30, 30));
	pEnvironment->set_shape(env_shape);
	vGameObjects.push_back(pEnvironment);
	pPlayer = std::make_shared<Player>(olc::vi2d(ScreenWidth() / 2, ScreenHeight() / 2));
	vGameObjects.push_back(pPlayer);
	pCamera = std::make_shared<Camera>(this, pPlayer);

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
	auto pxl_size = GetPixelSize();
	pPlayer->update(fElapsedTime, this);
	pCamera->update();
	pCamera->draw(vGameObjects);



	if (fElapsedTime < target_time_per_frame.count())
	{
		auto dur_to_sleep = target_time_per_frame - dElapsedTime;
		std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(dur_to_sleep));
	}

	return true;
}
