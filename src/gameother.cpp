# include <string.h>

# include "DxLib.h"

# include "gameother.hpp"


/* -------------------
	private
---------------------- */
void GameOther::SetPos() {

	// get font size (= height)
	GetFontStateToHandle(NULL, &size, NULL, font);

	// [round, bet]
	for (int i = 0; i < 2; i++) {
	
		pos[i][0] = 10;		// xmin
		pos[i][1] = size * i;	// ymin
	}

	return;
}



/* ------------------
	public
--------------------- */
// constructor & destructor
GameOther::GameOther(int n) :
	round(1),
	roundMax(n),
	bet(-1)
{

	font = CreateFontToHandle(NULL, 32, 4);
	white = GetColor(255, 255, 255);
	text[0] = "round: %d / %d";
	text[1] = "bet  : %d";
	textNotBet = "bet  : setting now";

	SetPos();
}




void GameOther::DrawOther() {

	// [round, bet]
	for (int i = 0; i < 2; i++) {
	
		int x = pos[i][0];
		int y = pos[i][1];
		const char* s = text[i];

		switch (i) {

			// round
			case 0:
				DrawFormatStringToHandle(x, y, white, font, s, round, roundMax);
				break;

			// bet
			case 1:
				// is bet > 0?
				if (bet > 0) {
					DrawFormatStringToHandle(x, y, white, font, s, bet);
				}
				else {
					DrawStringToHandle(x, y, textNotBet, white, font);
				}
				break;
		}
	}

	return;
}


void GameOther::SetRound(int n) {
	round = n;
	return;
}

void GameOther::SetBet(int n) {
	bet = n;
	return;
}
