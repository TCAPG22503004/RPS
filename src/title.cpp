# include <string.h>

# include "DxLib.h"

# include "title.hpp"
# include "click.hpp"


/* -----------------
	private
-------------------- */
void Title::SetPos() {

	// get font size (= height)
	size = GetFontSize();

	// get screen size
	GetScreenState(&x, &y, NULL);

	SetTitlePos();
	SetButtonPos();

	return;
}


void Title::SetTitlePos() {

	// xmin
	int len = GetDrawStringWidthToHandle(titleText, strlen(titleText), titleFont);
	titlePos[0] = (x/2) - (len/2);

	// ymin
	titlePos[1] = y / 16;

	return;
}


void Title::SetButtonPos() {

	// [start, quit]
	for (int i = 0; i < 2; i++) {

		// xmin
		const char* s = button[i];
		len[i] = GetDrawStringWidth(s, strlen(s));
		buttonPos[i][0] = (x / 3 * (i+1)) - (len[i]/2);

		// ymin
		buttonPos[i][1] = (y * 7 / 8) - (size/2);
	}

	return;
}


void Title::Draw() {

	ClearDrawScreen();

	// title
	int x = titlePos[0];
	int y = titlePos[1];
	const char* s = titleText;
	DrawStringToHandle(x, y, s, white, titleFont);

	// button
	// [start, quit]
	for (int i = 0; i < 2; i++) {
		x = buttonPos[i][0];
		y = buttonPos[i][1];
		s = button[i];
		DrawString(x, y, s, red);
	}

	ScreenFlip();

	return;
}


int Title::PushedButton() {

	// mouse
	int x, y;
	GetMousePoint(&x, &y);

	// [start, quit]
	for (int i = 0; i < 2; i++) {

		int xb = buttonPos[i][0];
		int yb = buttonPos[i][1];
		int l = len[i];

		bool isX = ((x >= xb) && (x <= xb + l));
		bool isY = ((y >= yb) && (y <= yb + size));

		// which button?
		if (isX && isY) {
			switch (i) {

				// start
				case 0:
					return 1;

				// quit
				case 1:
					return -1;
			}
		}
	}

	// not click on button
	return 0;
}


/* ----------------
	public
------------------- */
// constructor & destructor
Title::Title() {

	white = GetColor(255, 255, 255);
	red = GetColor(255, 64, 64);
	titleFont = CreateFontToHandle(NULL, 128, 8);
	titleText = "Reflect on\nPlaying\nStrategy";
	button[0] = "はじめる";
	button[1] = "おわる";

	SetPos();
}

Title::~Title() {

	// dxlib function
	InitFontToHandle();

}




int Title::title() {

	// draw
	Draw();

	// wait select button
	Click click;
	click.Init();

	int result = 0;

	while (result == 0) {

		// is click?
		if (click.IsClick()) result = PushedButton();

		// other
		if (ProcessMessage() == -1) result = -1;
		WaitTimer(1000/60);
	}

	// change mode
	return result;
}
