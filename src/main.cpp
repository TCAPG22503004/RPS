# include "DxLib.h"

# include "title.hpp"
# include "menu.hpp"
# include "game.hpp"
# include "result.hpp"

void GameLoop(){

	// other class
	Title title;
	Menu menu;
	Game game;
	Result result;

	// variant
	char name[2][16];
	int point[2];
	char room[16];
	int mode;
	
	// loop
	int scene = 0;

	while (scene != -1) {

		switch (scene) {

			case 0:
				scene = title.title();
				break;

			case 1:
				scene = menu.menu(name, room, &mode);
				break;

			case 2:
				scene = game.game(name, room, point, mode);
				break;

			case 3:
				scene = result.result(name, point);
				break;

			default:
				scene = -1;
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
	SetAlwaysRunFlag(TRUE);

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
