# include "DxLib.h"

# include "mystring.hpp"


/* -------------------
	private
---------------------- */
void MyString::SetTextPos() {

	// get font size (= height)
	int size;
	GetFontStateToHandle(NULL, &size, NULL, font);

	// get screen size
	int x, y;
	GetScreenState(&x, &y, NULL);


	// [rock, scissors, paper]
	for (int i = 0; i < 3; i++) {

		// targer text
		const char* s = textHover[i];

		// get length (= width)
		int len = GetDrawStringWidthToHandle(s, strlen(s), font);


		// set position
		textPos[i][0] = (x/2) - (len/2);	// xmin
		textPos[i][1] = y - size;		// ymin
	}

	return;
}



/* ------------------
	public
--------------------- */
void MyString::Init() {

	font = CreateFontToHandle(NULL, 64, 4); 
	white = GetColor(255, 255, 255);
	textHover[0] = "グー";
	textHover[1] = "チョキ";
	textHover[2] = "パー";

	SetTextPos();

	return;
}


void MyString::End() {

	InitFontToHandle();

	return;
}



void MyString::DrawSelect(int hover) {

	if (hover == -1) return;

	int x = textPos[hover][0];
	int y = textPos[hover][1];
	const char* s = textHover[hover];

	DrawStringToHandle(x, y, s, white, font);

	return;
}
