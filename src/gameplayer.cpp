# include "DxLib.h"

# include "gameplayer.hpp"


/* -------------------
	private
---------------------- */
void GamePlayer::SetPos() {

	// get font size (= height)
	GetFontStateToHandle(NULL, &size, NULL, font);

	// [player1, player2]
	for (int i = 0; i < 2; i++) {

		// [xmin, ymin]
		for (int j = 0; j < 2; j++) {

			pos[i][j] = size * i * j;

		}
	}

	return;
}



/* ------------------
	public
--------------------- */
// constructor & destructor
GamePlayer::GamePlayer() {

	font = CreateFontToHandle(NULL, 32, 4);
	white = GetColor(255, 255, 255);
	text = "player%d: %s (point: %d)";
	name[0] = "testUserAAA";
	name[1] = "testUserBBB";
	point[0] = 10;
	point[1] = 20;

	SetPos();
}

GamePlayer::~GamePlayer() {

	// DxLib function
	InitFontToHandle();

}




void GamePlayer::DrawPlayer() {

	// [player1, player2]
	for (int i = 0; i < 2; i++) {

		int n = i + 1;
		int x = pos[i][0];
		int y = pos[i][1];
		const char* s = name[i];
		int p = point[i];

		DrawFormatStringToHandle(x, y, white, font, text, n, s, p);
	}

	return;
}
