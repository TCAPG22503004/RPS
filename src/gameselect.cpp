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
	SetPlayerPos();
	SetWaitPos();

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

	return;
}


void GameSelect::SetPlayerPos() {

	// xmin
	textPlayerPos[0] = 10;

	// ymin
	textPlayerPos[1] = (y * 1 / 4) - (size/2);

	return;
}


void GameSelect::SetWaitPos() {

	// xmin
	int len = GetDrawStringWidth(wait, strlen(wait));
	waitPos[0] = (x/2) - (len/2);

	// ymin
	waitPos[1] = (y/2) - (size/2);

	return;
}




/* ------------------
	public
--------------------- */
// constructor
GameSelect::GameSelect() {

	white = GetColor(255, 255, 255);
	textHover[0] = "グー";
	textHover[1] = "チョキ";
	textHover[2] = "パー";
	textPlayer = "%s %s のターン";
	textTurn[0] = "先攻";
	textTurn[1] = "後攻";
	wait = "対戦相手の選択中...";

	SetTextPos();
}




void GameSelect::DrawSelect(int hover, int n, const char* name) {

	// string
	int x = textPlayerPos[0];
	int y = textPlayerPos[1];
	const char* s = textTurn[n-1];

	DrawFormatString(x, y, white, textPlayer, s, name);



	// hover
	if (hover == -1) return;	// not hovering

	x = textHoverPos[hover][0];
	y = textHoverPos[hover][1];
	s = textHover[hover];

	DrawString(x, y, s, white);

	return;
}


void GameSelect::DrawSelectWait() {
	
	int x = waitPos[0];
	int y = waitPos[1];
	const char* s = wait;

	DrawString(x, y, s, white);

	return;
}
