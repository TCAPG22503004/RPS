# include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {

	SetGraphMode(1280, 720, 16);
	SetMainWindowText("RPS");
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	WaitKey();

	DxLib_End();
	return 0;
}
