# include "DxLib.h"

# include "game.hpp"
# include "gameimage.hpp"
# include "gamebet.hpp"
# include "gameselect.hpp"
# include "gameresult.hpp"
# include "gameplayer.hpp"
# include "click.hpp"


/* ------------------
	private
--------------------- */
int Game::BetTurn() {

	//draw
	Draw(0);

	// click
	if (click->IsClick()) {
		
		if (bet->ChangeOrGoToNext()) {

			nBet = bet->GetBet();

			return 1;
		}
	}

	return 0;

}


int Game::SelectTurn(int n) {

	// get mouse position
	hover = img->CheckHover();

	// draw
	Draw(1);

	// after choice
	if (click->IsClick()) {
		select[n] = hover;
		if (select[n] != -1) return (n+2);
	}

	return (n+1);

}


int Game::FirstPlayerTurn() {

	return SelectTurn(0);
}


int Game::SecondPlayerTurn() {

	return SelectTurn(1);
}


int Game::ResultTurn() {

	// draw
	Draw(2);

	// next turn
	if (click->IsClick()) {

		// is last round?
		round++;

		if (round > roundMax) {
			return -1;
		}
		else {
			bet->ChangeBet(-999);
			return 0;
		}
	}

	return 3;
}


void Game::Draw(int n) {

	ClearDrawScreen();

	ply->DrawPlayer();

	switch(n) {
		case 0:
			bet->DrawBet();
			break;

		case 1:
			img->DrawSelect();
			slc->DrawSelect(hover, round, nBet);

			break;

		case 2:
			img->DrawResult(select[0], select[1]);
			rsl->DrawResult(select[0], select[1]);
			break;
	}

	ScreenFlip();

	return;
}



/* ----------------
	public
------------------- */
// constructor & destructor
Game::Game() :
	img(new GameImage),
	bet(new GameBet),
	slc(new GameSelect),
	rsl(new GameResult),
	ply(new GamePlayer),
	click(new Click),
	round(1),
	roundMax(3)
{
}

Game::~Game() {

	delete img;
	delete bet;
	delete slc;
	delete rsl;
	delete ply;
	delete click;
}



// function
int Game::test() {

	int turn = 0;
	bool isLoop = true;

	while (isLoop) {

		switch (turn) {

			case 0:
				turn = BetTurn();
				break;

			case 1:
				turn = FirstPlayerTurn();
				break;
		
			case 2:
				turn = SecondPlayerTurn();
				break;
		
			case 3:
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
