# include "DxLib.h"

# include "gamestring.hpp"


/* -------------------
	private
---------------------- */
void GameString::SetTextPos() {

	// get font size (= height)
	int size;
	GetFontStateToHandle(NULL, &size, NULL, font);

	// get screen size
	int x, y;
	GetScreenState(&x, &y, NULL);


	// [rock, scissors, paper]
	for (int i = 0; i < 3; i++) {

		// targer text
		const char* s1 = textHover[i];
		const char* s2 = textResult[i];

		// get length (= width)
		int len1 = GetDrawStringWidthToHandle(s1, strlen(s1), font);
		int len2 = GetDrawStringWidthToHandle(s2, strlen(s2), font);


		// set position
		textHoverPos[i][0] = (x/2) - (len1/2);	// xmin
		textHoverPos[i][1] = y - size;		// ymin

		textResultPos[i][0] = (x/2) - (len2/2);	// xmin
		textResultPos[i][1] = 0;		// ymin
	}

	return;
}



/* ------------------
	public
--------------------- */
void GameString::Init() {

	font = CreateFontToHandle(NULL, 64, 4); 
	white = GetColor(255, 255, 255);
	textHover[0] = "グー";
	textHover[1] = "チョキ";
	textHover[2] = "パー";
	textResult[0] = "あいこ";
	textResult[1] = "負け";
	textResult[2] = "勝ち";

	SetTextPos();

	return;
}


void GameString::End() {

	InitFontToHandle();

	return;
}



void GameString::DrawSelect(int hover) {

	if (hover == -1) return;

	int x = textHoverPos[hover][0];
	int y = textHoverPos[hover][1];
	const char* s = textHover[hover];

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
