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
GameOther::GameOther() :
	round(1),
	bet(-1)
{

	font = CreateFontToHandle(NULL, 32, 4);
	white = GetColor(255, 255, 255);
	text[0] = "round: %d";
	text[1] = "bet  : %d";
	textNotBet = "bet  : setting now";

	SetPos();
}




void GameOther::DrawOther() {

	int n[2] = {round, bet};

	// [round, bet]
	for (int i = 0; i < 2; i++) {
	
		int x = pos[i][0];
		int y = pos[i][1];
		const char* s = text[i];
		int m = n[i];

		// is bet > 0?
		if (m > 0) {
			DrawFormatStringToHandle(x, y, white, font, s, m);
		}
		else {
			DrawStringToHandle(x, y, textNotBet, white, font);
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
