# include "DxLib.h"

# include "gameresult.hpp"


/* -------------------
	private
---------------------- */
void GameResult::SetTextPos() {

	// get font size (= height)
	size = GetFontSize();

	// get screen size
	GetScreenState(&x, &y, NULL);

	SetResultPos();

	return;
}


void GameResult::SetResultPos() {

	// [draw, lose, win]
	for (int i = 0; i < 3; i++) {

		// xmin
		const char* s = textResult[i];
		int len = GetDrawStringWidth(s, strlen(s));
		textResultPos[i][0] = (x/2) - (len/2);

		// ymin
		textResultPos[i][1] = y * 1 / 4;
	}
}




/* ------------------
	public
--------------------- */
// constructor
GameResult::GameResult() {

	white = GetColor(255, 255, 255);
	textResult[0] = "あいこ";
	textResult[1] = "負け";
	textResult[2] = "勝ち";

	SetTextPos();
}




void GameResult::DrawResult(int n, int m) {

	int result = (n - m + 3) % 3;

	int x = textResultPos[result][0];
	int y = textResultPos[result][1];
	const char* s = textResult[result];

	DrawString(x, y, s, white);

	return;
}
