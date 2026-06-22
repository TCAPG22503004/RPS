# include "DxLib.h"

# include "gameplayer.hpp"


/* -------------------
	private
---------------------- */
void GamePlayer::SetPos() {

	// get font size (= height)
	GetFontStateToHandle(NULL, &size, NULL, font);

	// get text length
	len = GetDrawFormatStringWidthToHandle(font, text, 1, "ああああああああ", 999);

	// get screen size
	GetScreenState(&x, &y, NULL);

	// set pos
	pos[0] = x - len;			// xmin
	pos[1] = size * (playerNumber - 1);	// ymin

	return;
}



/* ------------------
	public
--------------------- */
// constructor & destructor
GamePlayer::GamePlayer(int n, int p, const char* s) {

	font = CreateFontToHandle(NULL, 32, 4);
	white = GetColor(255, 255, 255);
	text = "player%d: %s (point: %d)";
	point = p;
	playerNumber = n;
	name = s;

	SetPos();
}

GamePlayer::~GamePlayer() {

	// DxLib function
	InitFontToHandle();

}




void GamePlayer::DrawPlayer() {

	int x = pos[0];
	int y = pos[1];
	const char* s = text;
	int n = playerNumber;
	const char* t = name;
	int p = point;

	DrawFormatStringToHandle(x, y, white, font, s, n, t, p);

	return;
}


bool GamePlayer::DecideHand(int n) {

	if (n >= 0 && n <= 2) {
		hand = n;
		return true;
	}

	return false;
}

bool GamePlayer::ChangePoint(int n) {

	point += n;

	// gameover if minus
	if (point < 0) return true;

	return false;
}


int GamePlayer::GetHand() {
	return hand;
}

const char* GamePlayer::GetName() {
	return name;
}

int GamePlayer::GetPoint() {
	return point;
}

void GamePlayer::InitPoint(int n) {
	point = n;
	return;
}
