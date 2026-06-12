# include "DxLib.h"

# include "gamestring.hpp"


/* -------------------
	private
---------------------- */
void GameString::SetTextPos() {

	// get font size (= height)
	GetFontStateToHandle(NULL, &size, NULL, font);

	// get screen size
	GetScreenState(&x, &y, NULL);

	SetHoverAndResultPos();
	SetOtherPos();

	return;
}


void GameString::SetHoverAndResultPos() {

	for (int i = 0; i < 3; i++) {

		// [rock, scissors, paper]
		SetCenter(textHover[i], textHoverPos[i]);	// xmin
		textHoverPos[i][1] = y - size;			// ymin

		// [draw, lose, win]
		SetCenter(textResult[i], textResultPos[i]);	// xmin
		textResultPos[i][1] = 0;			// ymin
	}


}


void GameString::SetOtherPos() {

	// "player: "
	textOtherPos[0][0] = 0;
	textOtherPos[0][1] = 0;

	// player name
	int len = GetDrawStringWidthToHandle(textOther[0], strlen(textOther[0]), font);
	textOtherPos[1][0] = len;
	textOtherPos[1][1] = 0;

	// "bet: "
	textOtherPos[2][0] = 0;
	textOtherPos[2][1] = size;

	// "入力~ " or amount
	len = GetDrawStringWidthToHandle(textOther[0], strlen(textOther[0]), font);
	textOtherPos[3][0] = len;
	textOtherPos[3][1] = size;

	return;
}


void GameString::SetCenter(const char* s, int pos[2]) {

	int len = GetDrawStringWidthToHandle(s, strlen(s), font);

	pos[0] = (x/2) - (len/2);

	return;
}






/* ------------------
	public
--------------------- */
// constructor & destructor
GameString::GameString() {

	font = CreateFontToHandle(NULL, 64, 4); 
	white = GetColor(255, 255, 255);
	textHover[0] = "グー";
	textHover[1] = "チョキ";
	textHover[2] = "パー";
	textResult[0] = "あいこ";
	textResult[1] = "負け";
	textResult[2] = "勝ち";
	textOther[0] = "player: ";
	textOther[1] = "bet   : ";
	textOther[2] = "入力(1以上) →";

	SetTextPos();
}


GameString::~GameString() {

	// dxlib function
	InitFontToHandle();

	return;
}



void GameString::DrawSelect(int hover, const char* name, int n) {

	// "player: "
	int x = textOtherPos[0][0];
	int y = textOtherPos[0][1];
	const char* s = textOther[0];

	DrawStringToHandle(x, y, s, white, font);

	// player name
	x = textOtherPos[1][0];
	y = textOtherPos[1][1];

	DrawStringToHandle(x, y, name, white, font);

	// "bet: "
	x = textOtherPos[2][0];
	y = textOtherPos[2][1];
	s = textOther[1];

	DrawStringToHandle(x, y, s, white, font);

	// "入力~ " or amount
	x = textOtherPos[3][0];
	y = textOtherPos[3][1];
	if (n < 1) {
		s = textOther[2];
		DrawStringToHandle(x, y, s, white, font);
	}
	else {
		DrawFormatStringToHandle(x, y, white, font, "%d", n);
	}


	// not hovering
	if (hover == -1) return;

	// hovering
	x = textHoverPos[hover][0];
	y = textHoverPos[hover][1];
	s = textHover[hover];

	DrawStringToHandle(x, y, s, white, font);

	return;
}


void GameString::DrawResult(int n, int m) {

	int result = (n - m + 3) % 3;

	int x = textResultPos[result][0];
	int y = textResultPos[result][1];
	const char* s = textResult[result];

	DrawStringToHandle(x, y, s, white, font);

	return;
}
