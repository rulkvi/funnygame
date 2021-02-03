#include "funnygame.h"

int main()
{
	FunnyGame game;
	if (game.Construct(256, 180, 4, 4))
		game.Start();
	return 0;
}