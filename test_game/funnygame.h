#include <optional>
#include <chrono>
#include <thread>
#include "shape.h"
#include "world.h"
#include "camera.h"
#include "environment.h"
#include "olcFramework.h"
#include "Player.h"

using namespace std::literals;


class FunnyGame : public olc::PixelGameEngine
{
	std::vector<std::shared_ptr<RectangleShape>> vShapes;
	std::vector<std::shared_ptr<Game_object>> vGameObjects;
	olc::vi2d m_vi_G{ 0, 1000 };
	olc::Renderable gfxTiles;
	std::chrono::duration<float> target_time_per_frame = 1000ms / 60;
	std::shared_ptr<Shape> pSelectedShape = nullptr;
	std::shared_ptr<Player> pPlayer = nullptr;
	std::shared_ptr<Camera> pCamera = nullptr;
	std::shared_ptr<Environment_obj> pEnvironment = nullptr;

public:
	FunnyGame()
	{
		sAppName = "FunnyGame";
	}
public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};

