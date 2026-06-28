# include <string.h>

# include "DxLib.h"

# include "gameonline.hpp"
# include "mysql.hpp"

// static
char* GameOnline::other;

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

	// connect
	isConnect = sql->Connect();

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

bool GameOnline::IsPushButton() {

	// mouse position
	int x, y;
	GetMousePoint(&x, &y);

	// click back
	bool isX = ((x >= buttonPos[0]) && (x <= buttonPos[0] + lenButton));
	bool isY = ((y >= buttonPos[1]) && (y <= buttonPos[1] + size));

	return (isX && isY);
}



int GameOnline::InitRoom(char name[2][16], char room[16], bool *isPlayer1) {

	// Draw
	DrawRoom(room);

	// can connect?
	if (isConnect == false) return -1;

	// using other pair? (or error happen?)
	int n = sql->CountExistRoomID(room);
	if (n < 0) return -1;
	if (n >= 2) return -2;

	// is exist other player?
	*isPlayer1 = (n == 0);
	bool isSameName = false;;
	if (*isPlayer1 == false) {
		other = sql->GetOtherPlayerName(room);
		isSameName = (strcmp(other, name[0]) == 0);
	}

	// create user data
	if (isSameName) return -3;	// avoid same name
	if (sql->Insert(name[0], room) == false) return -1;

	// wait for player2
	if (*isPlayer1) {
		while (true) {

			// break if appear player
			if (sql->CountExistRoomID(room) == 2) {
				other = sql->GetOtherPlayerName(room);
				break;
			}

			// other
			if (ProcessMessage() == -1) return -999;
			WaitTimer(1000);
		}
	}

	// set other player name
	for (int i = 0; i < 16; i++) {
		name[1][i] = other[i];
	}

	return 0;
}
