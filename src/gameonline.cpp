# include <string.h>
# include <cstdlib>

# include "DxLib.h"

# include "gameonline.hpp"
# include "mysql.hpp"
# include "click.hpp"


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
	textRoundPos[0] = 0;

	// ymin
	textRoundPos[1] = y - size;

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


bool GameOnline::IsPushButton() {

	// mouse position
	int x, y;
	GetMousePoint(&x, &y);

	// click back
	bool isX = ((x >= buttonPos[0]) && (x <= buttonPos[0] + lenButton));
	bool isY = ((y >= buttonPos[1]) && (y <= buttonPos[1] + size));

	return (isX && isY);
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


void GameOnline::DrawError(int n) {

	const char* s;

	if (n == 0) s = "部屋ID のエラーです。\n他のIDを試して下さい。\n\nメニュー画面に戻ります...";
	else s = "名前 のエラーです。\n他の名前を試して下さい。\n\nメニュー画面に戻ります...";

	ClearDrawScreen();
	DrawString(0, 0, s, white);
	ScreenFlip();

	return;
}


void GameOnline::DrawRound() {
	
	int x = textRoundPos[0];
	int y = textRoundPos[1];
	const char* s = textRound;

	DrawString(x, y, s, white);

	// draw
	ScreenFlip();

	return;
}


int GameOnline::InitRoom(char names[2][16], char room[16], bool *isPlayer1) {

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
		sql->GetOtherPlayerName(room, other);
		DrawString(100, 100, other, white);
		ScreenFlip();
		isSameName = (strcmp(other, names[0]) == 0);
	}

	// create user data
	if (isSameName) return -3;	// avoid same name
	if (sql->Insert(names[0], room) == false) return -1;

	// wait for player2
	if (*isPlayer1) {

		int time = GetNowCount();
		Click click;

		while (true) {

			// check per 1 second
			if (GetNowCount() - time >= 1000) {
				time = GetNowCount();

				// break if appear player
				if (sql->CountExistRoomID(room) == 2) {
					sql->GetOtherPlayerName(room, other);
					break;
				}
			}

			// back title
			if (click.IsClick() && IsPushButton()) {
				DeleteUser(names, room);
				return 1;
			}

			// other
			if (ProcessMessage() == -1) return -999;
			WaitTimer(1000/60);
		}
	}

	// set other player name
	for (int i = 0; i < 16; i++) {
		names[1][i] = other[i];
	}

	return 0;
}


int GameOnline::WaitRound(char name[16], char room[16], int n, bool isTurnEnd) {

	int result = -1;

	int time = GetNowCount();

	while (true) {

		// access server per 1 sec
		if (GetNowCount() - time >= 1000) {
			time = GetNowCount();

			// is finished?
			result = GetData(name, room, n);
			bool b = (result == -1);
			if (b == isTurnEnd) break;
		}

		// other
		if (ProcessMessage() == -1) return -999;
		WaitTimer(1000/60);
	}

	return result;
}


int GameOnline::GetData(char name[16], char room[16], int n) {

	// get by server
	char s[16];
	sql->Select(name, room, n, s);

	// return int
	int m = std::atoi(s);
	return m;
}


void GameOnline::SetData(char name[16], char room[16], const char* s, int n) {

	sql->Update(name, room, s, n);

	return;
}


int GameOnline::DeleteUser(char names[2][16], char room[16]) {

	if (names[0] != nullptr) sql->Delete(names[0], room);
	if (names[1] != nullptr) sql->Delete(names[1], room);

	return 0;
}
