# include <string.h>

# include "DxLib.h"

# include "game.hpp"
# include "myimage.hpp"


/* ------------------
	private
--------------------- */

void Game::Init() {
	
	// set string
	font = CreateFontToHandle(NULL, 64, 4); 
	white = GetColor(255, 255, 255);
	hoverGu = "グー";
	hoverChoki = "チョキ";
	hoverPa = "パー";

	SetTextPos(hoverGu, 0);
	SetTextPos(hoverChoki, 1);
	SetTextPos(hoverPa, 2);

	return;
}


void Game::SetTextPos(const char* s, int n) {

	int len = GetDrawStringWidthToHandle(s, strlen(s), font);
	int size;
	GetFontStateToHandle(NULL, &size, NULL, font);
	
	txtPos[n][0] = (x/2) - (len/2);
	txtPos[n][1] = y - size;

	return;
}



void Game::Draw() {


	//text
	switch (hover) {
		case 0:
			DrawStringToHandle(txtPos[0][0], txtPos[0][1], hoverGu, white, font);
			break;

		case 1:
			DrawStringToHandle(txtPos[1][0], txtPos[1][1], hoverChoki, white, font);
			break;

		case 2:
			DrawStringToHandle(txtPos[2][0], txtPos[2][1], hoverPa, white, font);
			break;

		default:
			break;
	}

	DrawFormatStringToHandle(0, 0, white, font, "%d", select);


	return;
}


/* ----------------
	public
------------------- */

int Game::test() {

	Init();

	MyImage img;
	img.Init();

	while (true) {

		hover = img.CheckHover();
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) select = hover;

		ClearDrawScreen();
		Draw();
		img.DrawSelect();
		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (ProcessMessage() == -1) break;
		WaitTimer(1000/60);
	}

	InitFontToHandle();
	img.End();

	return -1;
}
