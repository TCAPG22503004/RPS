# include "DxLib.h"

# include "game.hpp"
# include "gameimage.hpp"
# include "gameselect.hpp"
# include "gameresult.hpp"
# include "click.hpp"


/* ------------------
	private
--------------------- */
int Game::SelectTurn(int n) {

	// get mouse position
	hover = img->CheckHover();

	// draw
	ClearDrawScreen();

	img->DrawSelect();

	// (test)
	const char* s[2] = {"AAA", "BBB"};
	int m[2] = {10, 20};
	slc->DrawSelect(hover, round, 10, (n == 0), s, m);

	ScreenFlip();

	// after choice
	if (click->IsClick()) {
		select[n] = hover;
		if (select[n] != -1) return (n+1);
	}

	return n;

}


int Game::FirstPlayerTurn() {

	return SelectTurn(0);
}


int Game::SecondPlayerTurn() {

	return SelectTurn(1);
}


int Game::ResultTurn() {

	// draw
	ClearDrawScreen();

	img->DrawResult(select[0], select[1]);
	rsl->DrawResult(select[0], select[1]);

	ScreenFlip();


	// next turn
	if (click->IsClick()) {

		// is last round?
		round++;

		if (round > roundMax) {
			return -1;
		}
		else {
			return 0;
		}
	}

	return 2;
}



/* ----------------
	public
------------------- */
// constructor & destructor
Game::Game() :
	img(new GameImage),
	slc(new GameSelect),
	rsl(new GameResult),
	click(new Click),
	round(1),
	roundMax(3)
{
}

Game::~Game() {

	delete img;
	delete slc;
	delete rsl;
	delete click;
}



// function
int Game::test() {

	int turn = 0;
	bool isLoop = true;

	while (isLoop) {

		switch (turn) {

			case 0:
				turn = FirstPlayerTurn();
				break;
		
			case 1:
				turn = SecondPlayerTurn();
				break;
		
			case 2:
				turn = ResultTurn();
				break;

			default:
				isLoop = false;
				break;
		}


		// other
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (ProcessMessage() == -1) break;
		WaitTimer(1000/60);
	}

	return -1;
}
