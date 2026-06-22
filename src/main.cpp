# include "DxLib.h"

# include "title.hpp"
# include "game.hpp"
# include "result.hpp"

void GameLoop() {

	Title title;
	Game game;
	Result result;

	int mode = 0;

	while (mode != -1) {

		switch (mode) {

			case 0:
				mode = title.title();
				break;

			case 1:
				mode = game.game();
				break;

			case 2:
				mode = result.result();
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
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) return -1;

	SetFontSize(64);
	SetFontThickness(4);
	SetDrawScreen(DX_SCREEN_BACK);

	// start loop
	GameLoop();

	// end
	DxLib_End();
	return 0;
}
