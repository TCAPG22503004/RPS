# include "DxLib.h"

# include "game.hpp"

void GameLoop() {

	Game game;

	int mode = 1;

	while (mode != -1) {

		switch (mode) {

			case 1:
				mode = game.test();
				break;

			default:
				mode = -1;
				break;
		}

		// abnormal end
		if (ProcessMessage() == -1) break;
	}

	return;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	// dxlib setting
	SetGraphMode(1280, 720, 16);
	SetMainWindowText("RPS");
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	// start loop
	GameLoop();

	// end
	DxLib_End();
	return 0;
}
