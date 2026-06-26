# include <string.h>

# include "DxLib.h"

# include "gameonline.hpp"
# include "mysql.hpp"


/* -------------------
	private
---------------------- */
void GameOnline::SetPos() {

	// get font size (= height)
	size = GetFontSize();

	// get screen size
	GetScreenState(&x, &y, NULL);

	SetRoomPos();
	SetRoundPos();
	SetButtonPos();

	return;
}

void GameOnline::SetRoomPos() {

	// xmin
	int len = GetDrawFormatStringWidth(textRoom, "abcdefghijkl");
	textRoomPos[0] = (x/2) - (len/2);

	// ymin
	textRoomPos[1] = (y/3) - size;

	return;
}


void GameOnline::SetRoundPos() {

	// xmin
	int len = GetDrawStringWidth(textRound, strlen(textRound));
	textRoundPos[0] = (x/2) - (len/2);

	// ymin
	textRoundPos[1] = (y/2) - (size/2);

	return;
}


void GameOnline::SetButtonPos() {

	// xmin
	lenButton = GetDrawStringWidth(button, strlen(button));
	buttonPos[0] = (x/2) - (lenButton/2);

	// ymin
	buttonPos[1] = (y * 2 / 3) - (size/2);

	return;
}



/* ------------------
	public
--------------------- */
// constructor & destructor
GameOnline::GameOnline() :
	sql(new MysqlClass)
{

	white = GetColor(255, 255, 255);
	red = GetColor(255, 64, 64);
	textRoom = "部屋のID = %s\n他のプレイヤーを待っています...";
	textRound = "通信待機中...";
	button = "モード選択へ戻る";

	SetPos();
}

GameOnline::~GameOnline() {
	delete sql;
}


void GameOnline::DrawRoom(char room[16]) {
	
	// clear
	ClearDrawScreen();

	// text
	int x = textRoomPos[0];
	int y = textRoomPos[1];
	const char* s = textRoom;

	DrawFormatString(x, y, white, s, room);

	// button
	x = buttonPos[0];
	y = buttonPos[1];
	s = button;

	DrawString(x, y, s, red);

	// draw
	ScreenFlip();

	return;
}

void GameOnline::DrawRound() {
	
	int x = textRoundPos[0];
	int y = textRoundPos[1];
	const char* s = textRound;

	DrawString(x, y, s, white);

	return;
}

bool GameOnline::IsBack() {

	// mouse position
	int x, y;
	GetMousePoint(&x, &y);

	// click back
	bool isX = ((x >= buttonPos[0]) && (x <= buttonPos[0] + lenButton));
	bool isY = ((y >= buttonPos[1]) && (y <= buttonPos[1] + size));

	return (isX && isY);
}



int GameOnline::MakeRoom(char name[16], char room[16]) {

	// can connect?
	if (sql->Connect() == false) return -1;

	// using other pair? (or error happen?)
	int n = sql->CountExistRoomID(room);
	if (n < 0) return -1;
	if (n >= 2) return -2;

	// create room
	if (sql->Insert(name, room) == false) return -1;

	return 0;
}
