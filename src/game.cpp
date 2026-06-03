# include "DxLib.h"

# include "game.hpp"


int Game::test() {

	DrawString(0, 0, "Hello, World!", GetColor(255, 255, 255));
	ScreenFlip();

	WaitKey();

	return -1;
}
