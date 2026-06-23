# include <string.h>

# include "DxLib.h"

# include "menu.hpp"
# include "click.hpp"


/* -----------------
	private
-------------------- */
void Menu::SetPos() {

	// get font size (= height)
	size = GetFontSize();

	// get screen size
	GetScreenState(&x, &y, NULL);

	// get font height
	GetFontStateToHandle(NULL, &h, NULL, font);

	// [solo, local, global]
	for (int i = 0; i < 3; i++) {

		// [button, box1, box2]
		for (int j = 0; j < 3; j++) {

			// xmin
			if (j == 0) {
				const char* s = button[i];
				len[i] = GetDrawStringWidth(s, strlen(s));
				clickPos[i][j][0] = (x/64 * (i*21+11)) - (len[i] / 2);
			}
			else {
				menuPos[i][j-1][0] = (x/64 * (i*21+11)) - (boxSize[0] / 2);
				clickPos[i][j][0] = menuPos[i][j-1][0];
			}
	
			// ymin
			if (j == 0) {
				clickPos[i][j][1] = (y/4) - (size/2);
			}
			else {
				menuPos[i][j-1][1] = (y/4 * (j+1)) - ((h + boxSize[1]) / 2);
				clickPos[i][j][1] = menuPos[i][j-1][1] + h;
			}
		}
	}

	// describe
	describePos[0] = 0;
	describePos[1] = 0;

	return;
}


void Menu::InputString(int n, int m) {

	// describe
	int x = describePos[0];
	int y = describePos[1];
	DrawString(x, y, "入力中... (Enterで確定, Escでキャンセル)", white);

	// invisible before text
	x = clickPos[n][m][0];
	y = clickPos[n][m][1];
	int x2 = x + boxSize[0];
	int y2 = y + boxSize[1];
	DrawBox(x, y, x2, y2, black, TRUE);
	DrawBox(x, y, x2, y2, white, FALSE);

	// input
	SetActiveKeyInput(inputHandle);
	x = clickPos[n][m][0];
	y = clickPos[n][m][1] + (boxSize[1] / 2) - (h/2);
	DrawKeyInputString(x, y, inputHandle);
	GetKeyInputString(input[n][m-1], inputHandle);

	return;
}


void Menu::Draw() {

	ClearDrawScreen();

	// [solo, local, global]
	for (int i = 0; i < 3; i++) {

		// [button, box1, box2]
		for (int j = 0; j < 3; j++) {

			if (i == 0 && j == 2) continue;	// nothing

			int x = clickPos[i][j][0];
			int y = clickPos[i][j][1];

			// button
			if (j == 0) {
				const char* s = button[i];
				DrawString(x, y, s, red);
			}

			// input field
			else {
				// describe
				int x2 = menuPos[i][j-1][0];
				int y2 = menuPos[i][j-1][1];
				const char* s = menuText[i][j-1];
		
				DrawStringToHandle(x2, y2, s, white, font);
	
				// box
				x2 = x + boxSize[0];
				y2 = y + boxSize[1];
	
				DrawBox(x, y, x2, y2, white, FALSE);

				// string
				x2 = x;
				y2 = y + (boxSize[1] / 2) - (h/2);
				DrawString(x2, y2, input[i][j-1], white);

			}
		}
	}

	// is hover button?
	int n, m;
	if (isHover(&n, &m) && m == 0) {
		int x = describePos[0];
		int y = describePos[1];
		const char* s = hover[n];
		DrawString(x, y, s, white);
	}

	ScreenFlip();

	return;
}

bool Menu::isHover(int *n, int *m) {

	// mouse
	int x, y;
	GetMousePoint(&x, &y);

	// [solo, local, global]
	for (int i = 0; i < 3; i++) {

		// [button, box1, box2]
		for (int j = 0; j < 3; j++) {

			if (i == 0 && j == 2) continue;	// nothing

			int xb = clickPos[i][j][0];
			int yb = clickPos[i][j][1];

			int w = (j == 0) ? len[i] : boxSize[0];	// button or box width
			int h = (j == 0) ? size : boxSize[1];	// button or box height
	
			bool isX = ((x >= xb) && (x <= xb + w));
			bool isY = ((y >= yb) && (y <= yb + h));
	
			// which object?
			if (isX && isY) {
				*n = i;
				*m = j;
				return true;
			}
		}
	}

	// not hover
	return false;
}



int Menu::OnClick() {

	// which object?
	int n, m;
	if (isHover(&n, &m) == false) return 1;	// not hover

	// button
	if (m == 0) {
		mode = n;
		return 2;
	}

	// input field
	else {
		InputString(n, m);
		return 1;
	}
}



/* ----------------
	public
------------------- */
// constructor & destructor
Menu::Menu() :
	mode(-1)
{

	font = CreateFontToHandle(NULL, 24, 4);
	white = GetColor(255, 255, 255);
	red = GetColor(255, 64, 64);
	black = GetColor(0, 0, 0);
	boxSize[0] = 400;
	boxSize[1] = 100;
	menuText[0][0] = "名前を入力";
	menuText[1][0] = "一人目の名前を入力";
	menuText[1][1] = "二人目の名前を入力";
	menuText[2][0] = "名前を入力";
	menuText[2][1] = "部屋のIDを入力";
	button[0] = "ひとりで";
	button[1] = "オフライン";
	button[2] = "オンライン";
	hover[0] = "CPUと戦います(クリックでスタート)";
	hover[1] = "二人で戦います(クリックでスタート)";
	hover[2] = "同じIDの人と戦います(クリックでスタート)";
	
	// create input handle
	inputHandle = MakeKeyInput(16, TRUE, FALSE, FALSE);

	SetPos();
}

Menu::~Menu() {

	// dxlib function
	InitFontToHandle();
	InitKeyInput();
}


int Menu::menu(const char* s[2], const char* id, int *m) {


	// wait select button
	Click click;
	click.Init();

	int result = 1;

	while (result == 1) {

		// draw
		Draw();

		// is click?
		if (click.IsClick()) result = OnClick();

		// other
		if (ProcessMessage() == -1) result = -1;
		WaitTimer(1000/60);
	}



	// set player information
	switch (mode) {

		// solo
		case 0:
			s[0] = input[0][0];
			s[1] = "CPU";
			break;

		// local
		case 1:
			s[0] = input[1][0];
			s[1] = input[1][1];
			break;

		// global
		case 2:
			s[0] = input[2][0];
			id = input[2][1];
			break;

		// (abnormal)
		default:
			break;
	}

	*m = mode;

	// change scene
	return result;
}
