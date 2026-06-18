# include <string.h>

# include "DxLib.h"

# include "gameselect.hpp"


/* -------------------
	private
---------------------- */
void GameSelect::SetTextPos() {

	// get font size (= height)
	size = GetFontSize();

	// get screen size
	GetScreenState(&x, &y, NULL);

	SetHoverPos();
	SetInfoPos();

	return;
}


void GameSelect::SetHoverPos() {

	// [rock, scissors, paper]
	for (int i = 0; i < 3; i++) {

		// xmin
		const char* s = textHover[i];
		int len = GetDrawStringWidth(s, strlen(s));
		textHoverPos[i][0] = (x/2) - (len/2);

		// ymin
		textHoverPos[i][1] = y - size;
	}
}


void GameSelect::SetInfoPos() {

	// [round, bet]
	for (int i = 0; i < 2; i++) {

		const char* s = textInfo[i];
		int len = GetDrawFormatStringWidth(s, 999);

		textInfoPos[i][0] = x - len;
		textInfoPos[i][1] = size * i;
	}

	return;
}




/* ------------------
	public
--------------------- */
// constructor & destructor
GameSelect::GameSelect() {

	white = GetColor(255, 255, 255);
	textHover[0] = "グー";
	textHover[1] = "チョキ";
	textHover[2] = "パー";
	textInfo[0] = "round : %d";
	textInfo[1] = "bet   : %d";

	SetTextPos();
}




void GameSelect::DrawSelect(int hover, int round, int bet) {


	// information
	for (int i = 0; i < 2; i++) {

		int x = textInfoPos[i][0];
		int y = textInfoPos[i][1];
		const char* s = textInfo[i];

		int n = (i == 0) ? round : bet;

		DrawFormatString(x, y, white, s, n);
	}


	// hover
	if (hover == -1) return;	// not hovering

	int x = textHoverPos[hover][0];
	int y = textHoverPos[hover][1];
	const char* s = textHover[hover];

	DrawString(x, y, s, white);

	return;
}
