# include <string.h>

# include "DxLib.h"

# include "game.hpp"


/* ------------------
	private
--------------------- */

void Game::Init() {
	
	// load images
	gu = LoadGraph("../img/janken_gu.png");
	choki = LoadGraph("../img/janken_choki.png");
	pa = LoadGraph("../img/janken_pa.png");

	// set position
	GetScreenState(&x, &y, NULL);

	SetImagePos(leftPos, 1);
	SetImagePos(centerPos, 2);
	SetImagePos(rightPos, 3);

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


void Game::SetImagePos(int pos[2][2], int n) {

	int size = x / 8;

	pos[0][0] = (x/4) * n - (size/2);
	pos[0][1] = (y/2) - (size/2);
	pos[1][0] = pos[0][0] + size;
	pos[1][1] = pos[0][1] + size;

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


void Game::SetHover() {

	GetMousePoint(&mousePos[0], &mousePos[1]);

	bool isX, isY;

	// left
	isX = (mousePos[0] >= leftPos[0][0]) && (mousePos[0] <= leftPos[1][0]);
	isY = (mousePos[1] >= leftPos[0][1]) && (mousePos[1] <= leftPos[1][1]);
	if (isX && isY) {
		hover = 0;
		return;
	}

	// center
	isX = (mousePos[0] >= centerPos[0][0]) && (mousePos[0] <= centerPos[1][0]);
	isY = (mousePos[1] >= centerPos[0][1]) && (mousePos[1] <= centerPos[1][1]);
	if (isX && isY) {
		hover = 1;
		return;
	}

	//right
	isX = (mousePos[0] >= rightPos[0][0]) && (mousePos[0] <= rightPos[1][0]);
	isY = (mousePos[1] >= rightPos[0][1]) && (mousePos[1] <= rightPos[1][1]);
	if (isX && isY) {
		hover = 2;
		return;
	}

	// not hovering
	hover = -1;

	return;
}


void Game::Draw() {

	ClearDrawScreen();

	// image
	DrawExtendGraph(leftPos[0][0], leftPos[0][1], leftPos[1][0], leftPos[1][1], gu, TRUE);
	DrawExtendGraph(centerPos[0][0], centerPos[0][1], centerPos[1][0], centerPos[1][1], choki, TRUE);
	DrawExtendGraph(rightPos[0][0], rightPos[0][1], rightPos[1][0], rightPos[1][1], pa, TRUE);

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


	ScreenFlip();

	return;
}


/* ----------------
	public
------------------- */

int Game::test() {

	Init();

	while (true) {

		SetHover();
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) select = hover;

		Draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (ProcessMessage() == -1) break;
		WaitTimer(1000/60);
	}

	InitGraph();

	return -1;
}
