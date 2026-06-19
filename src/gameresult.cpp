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
	SetInfoPos();

	return;
}


void GameResult::SetResultPos() {

	// xmin
	textResultPos[0] = 10;

	// ymin
	textResultPos[1] = (y * 1 / 4) - (size/2);

	return;
}


void GameResult::SetInfoPos() {

	// xmin
	int len = GetDrawStringWidth(textInfo, strlen(textInfo));
	textInfoPos[0] = (x/2) - (len/2);

	// ymin
	textInfoPos[1] = y - size;

	return;
}




/* ------------------
	public
--------------------- */
// constructor
GameResult::GameResult() {

	white = GetColor(255, 255, 255);
	textResult = "%s が %s\n%d + (%d*%d) = %d ポイントが移動します";
	textList[0] = "あいこになりました";
	textList[1] = "負けました";
	textList[2] = "勝ちました";
	textInfo = "クリックで進む";

	SetTextPos();
}




void GameResult::DrawResult(const char* name) {

	int x = textResultPos[0];
	int y = textResultPos[1];
	const char* s = textList[result];

	DrawFormatString(x, y, white, textResult, name, s, bet, bet, bonus, delta);

	// info
	x = textInfoPos[0];
	y = textInfoPos[1];
	s = textInfo;

	DrawString(x, y, s, white);

	return;
}

void GameResult::CalculateResult(int n, int m, int l) {

	// [draw, lose, win]
	result = (n - m + 3) % 3;

	// hand type
	int b[3] = {0, 2, 5};
	bonus = b[n];

	// delta point
	bet = l;
	if (result == 0) bet = 0;	// draw
	delta = bet + bet * bonus;

	return;
}


int GameResult::GetDelta(int n) {

	int m;

	switch (result) {

		//draw
		case 0:
			m = 0;
			break;

		// lose
		case 1:
			m = (n == 0) ? -delta : delta;
			break;

		// win
		case 2:
			m = (n == 0) ? delta : -delta;
			break;
	}
	
	return m;
}
