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

	for (int i = 0; i < 2; i++) {

		// round, bet
		textInfoPos[i][0] = 0;
		textInfoPos[i][1] = size * i;

		// player1, player2
		int len = GetDrawStringWidth(textInfo[i+2], strlen(textInfo[i+2]));
		textInfoPos[i+2][0] = x - len - 10;
		textInfoPos[i+2][1] = size * i;
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
	textInfo[2] = "%s player: %s (point: %d)";
	textInfo[3] = "%s player: %s (point: %d)";

	SetTextPos();
}




void GameSelect::DrawSelect(int hover, int round, int bet, bool is1st, const char* name[2], int point[2]) {

	// information
	int len = sizeof(textInfo) / sizeof(*textInfo);

	for (int i = 0; i < len; i++) {

		// information
		int x = textInfoPos[i][0];
		int y = textInfoPos[i][1];
		const char* s = textInfo[i];

		// " " or o or v
		const char *c1, *c2;
		bool isOdd = (round % 2 == 1);
		if (is1st) {
			c1 = isOdd ? "o" : " ";
			c2 = isOdd ? " " : "o";
		}
		else {
			c1 = isOdd ? "v" : "o";
			c2 = isOdd ? "o" : "v";
		}

		// draw
		switch (i) {

			case 0:
				DrawFormatString(x, y, white, s, round);
				break;
				
			case 1:
				DrawFormatString(x, y, white, s, bet);
				break;

			case 2:
				DrawFormatString(x, y, white, s, c1, name[0], point[0]);
				break;

			case 3:
				DrawFormatString(x, y, white, s, c2, name[1], point[1]);
				break;

		}
	}


	// hover
	if (hover == -1) return;	// not hovering

	int x = textHoverPos[hover][0];
	int y = textHoverPos[hover][1];
	const char* s = textHover[hover];

	DrawString(x, y, s, white);

	return;
}
