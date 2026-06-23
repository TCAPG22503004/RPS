# include <string.h>

# include "DxLib.h"

# include "result.hpp"
# include "click.hpp"


/* -----------------
	private
-------------------- */
void Result::SetPos() {

	// get font size (= height)
	size = GetFontSize();

	// get screen size
	GetScreenState(&x, &y, NULL);

	SetResultPos();
	SetButtonPos();

	return;
}


void Result::SetResultPos() {

	// [txt, player1, player2]
	for (int i = 0; i < 3; i++) {

		// xmin
		if (i == 0) {
			const char* s = resultText[i];
			int len = GetDrawStringWidth(s, strlen(s));
			resultPos[i][0] = (x/2) - (len/2);
		}
		else {
			resultPos[i][0] = 0;
		}

		// ymin
		resultPos[i][1] = (y / 5 * (i+1)) - (size/2);
	}

	return;
}


void Result::SetButtonPos() {

	// [retry, back]
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


void Result::Draw() {

	ClearDrawScreen();

	// result
	// [txt, player1, player2]
	for (int i = 0; i < 3; i++) {
		int x = resultPos[i][0];
		int y = resultPos[i][1];
		const char* s = resultText[i];

		if (i == 0) {
			DrawString(x, y, s, white);
		}
		else {
			const char* n = name[i-1];
			int p = point[i-1];
			DrawFormatString(x, y, white, s, n, p);
		}
	}

	// button
	// [retry, back]
	for (int i = 0; i < 2; i++) {
		int x = buttonPos[i][0];
		int y = buttonPos[i][1];
		const char* s = button[i];
		DrawString(x, y, s, red);
	}

	ScreenFlip();

	return;
}


int Result::PushedButton() {

	// mouse
	int x, y;
	GetMousePoint(&x, &y);

	// [retry, back]
	for (int i = 0; i < 2; i++) {

		int xb = buttonPos[i][0];
		int yb = buttonPos[i][1];
		int l = len[i];

		bool isX = ((x >= xb) && (x <= xb + l));
		bool isY = ((y >= yb) && (y <= yb + size));

		// which button?
		if (isX && isY) {
			switch (i) {

				// retry
				case 0:
					return 2;

				// title
				case 1:
					return 0;
			}
		}
	}

	// not click on button
	return 3;
}


/* ----------------
	public
------------------- */
// constructor & destructor
Result::Result() {

	white = GetColor(255, 255, 255);
	red = GetColor(255, 64, 64);
	resultText[0] = "Result";
	resultText[1] = "%s: %d point";
	resultText[2] = "%s: %d point";
	button[0] = "もういちど";
	button[1] = "タイトルへ";

	SetPos();
}



int Result::result(const char* s[2], int p[2]) {

	// set player data
	// [player1, player2]
	for (int i = 0; i < 2; i++) {
		name[i] = s[i];
		point[i] = p[i];
	}

	// draw
	Draw();

	// wait select button
	Click click;
	click.Init();

	int result = 3;

	while (result == 3) {

		// is click?
		if (click.IsClick()) result = PushedButton();

		// other
		if (ProcessMessage() == -1) result = -1;
		WaitTimer(1000/60);
	}

	// change mode
	return result;
}
