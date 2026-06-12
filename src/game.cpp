# include "DxLib.h"

# include "game.hpp"
# include "gameimage.hpp"
# include "gamestring.hpp"
# include "click.hpp"


/* ------------------
	private
--------------------- */
int Game::SelectTurn(int n, const char* name, int point){

	// get mouse position
	hover = img->CheckHover();

	// draw
	ClearDrawScreen();

	img->DrawSelect();
	str->DrawSelect(hover, name, point);

	ScreenFlip();

	// after choice
	if (click->IsClick()) {
		select[n] = hover;
		if (select[n] != -1) return (n+1);
	}

	return n;

}


int Game::FirstPlayerTurn() {

	return SelectTurn(0, "AAA", -1);
}


int Game::SecondPlayerTurn() {

	return SelectTurn(1, "BBB", 10);
}


int Game::ResultTurn() {

	// draw
	ClearDrawScreen();

	img->DrawResult(select[0], select[1]);
	str->DrawResult(select[0], select[1]);

	ScreenFlip();


	// next turn
	if (click->IsClick()) return 0;

	return 2;
}



/* ----------------
	public
------------------- */
// constructor & destructor
Game::Game() :
	img(new GameImage),
	str(new GameString),
	click(new Click),
	roundMax(10)
{
}

Game::~Game() {

	delete img;
	delete str;
	delete click;
}



// function
int Game::test() {

	int turn = 0;
	int round = 1;

	while (true) {

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
				break;
		}

		// break loop
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (ProcessMessage() == -1) break;
		WaitTimer(1000/60);
	}

	return -1;
}
