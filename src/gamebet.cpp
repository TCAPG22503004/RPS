# include <string.h>

# include "DxLib.h"

# include "gamebet.hpp"


/* -------------------
	private
---------------------- */
void GameBet::SetPos() {

	// get font size (= height)
	size = GetFontSize();

	// get screen size
	GetScreenState(&x, &y, NULL);

	SetTextPos();
	SetNumPos();
	SetButtonPos();
	SetNextPos();
	SetWaitPos();

	return;
}


void GameBet::SetTextPos() {

	// xmin
	int len = GetDrawStringWidth(text, strlen(text));
	textPos[0] = (x/2) - (len/2);

	// ymin
	textPos[1] = y * 1 / 4;

	return;
}

void GameBet::SetNumPos() {

	// xmin
	const char* n = "1";
	int len = GetDrawStringWidth(n, strlen(n));
	numPos[0] = (x/2) - (len/2);

	// ymin
	numPos[1] = (y*5/8) - (size/2);

	return;
}

void GameBet::SetButtonPos() {

	// [-10, -1, +1, +10]
	for (int i = 0; i < 4; i++) {
		
		// string
		const char* s = button[i];

		// x position: [-10, -1, (bet), +1, +10]
		int n = i + 1;
		if (i >= 2) n += 1;	// right of bet number

		// xmin
		lenButton[i] = GetDrawStringWidth(s, strlen(s));
		buttonPos[i][0] = (x/6 * n) - (lenButton[i]/2);

		// ymin
		buttonPos[i][1] = (y*5/8) - (size/2);

	}

	return;
}


void GameBet::SetNextPos() {

	// xmin
	lenNext = GetDrawStringWidth(next, strlen(next));
	nextPos[0] = (x/2) - (lenNext/2);

	// ymin
	nextPos[1] = y - size;

	return;
}

void GameBet::SetWaitPos() {

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
// constructor & destructor
GameBet::GameBet(int p) :

	bet(1),
	maxBet(p)
{
	white = GetColor(255, 255, 255);
	red = GetColor(255, 64, 64);	
	text = "賭けるポイントの量(クリックで設定)";
	button[0] = "-10";
	button[1] = "-1";
	button[2] = "+1";
	button[3] = "+10";
	next = "決定";
	wait = "基礎ポイントを設定中...";

	SetPos();
}


void GameBet::DrawBet() {

	// text
	DrawString(textPos[0], textPos[1], text, white);

	// num
	int x = numPos[0];
	int y = numPos[1];
	DrawFormatString(x, y, white, "%d", bet);

	// button
	for (int i = 0; i < 4; i++) {

		DrawString(buttonPos[i][0], buttonPos[i][1], button[i], red);

	}

	// next
	DrawString(nextPos[0], nextPos[1], next, red);

	return;
}


void GameBet::DrawBetWait() {

	DrawString(waitPos[0], waitPos[1], wait, white);

	return;
}




bool GameBet::ChangeOrGoToNext() {

	int x, y;
	GetMousePoint(&x, &y);

	// click next
	bool isX = ((x >= nextPos[0]) && (x <= nextPos[0] + lenNext));
	bool isY = ((y >= nextPos[1]) && (y <= nextPos[1] + size));
	if (isX && isY) return true;


	// change amount of bet
	int d[4] = {-10, -1, +1, +10};

	for (int i = 0; i < 4; i++) {

		isX = ((x >= buttonPos[i][0]) && (x <= buttonPos[i][0] + lenButton[i]));
		isY = ((y >= buttonPos[i][1]) && (y <= buttonPos[i][1] + size));

		if (isX && isY) {

			ChangeBet(d[i]);
			break;

		}
	}

	// (not click on next)
	return false;
}


void GameBet::ChangeBet(int n) {

	if (bet + n < 1) {
		bet = 1;
	}
	else if (bet + n > maxBet) {
		bet = maxBet;
	}
	else {
		bet += n;
	}

	return;
}

void GameBet::SetMaxBet(int n) {
	maxBet = n;
	return;
}

void GameBet::SetBetRandom() {

	// set bet (1 ~ max)
	bet = GetRand(maxBet - 1) + 1;

	// wait
	WaitTimer(1000);

	return;
}


void GameBet::SetBet(int n) {
	bet = n;
	return;
}

int GameBet::GetBet() {
	return bet;
}
