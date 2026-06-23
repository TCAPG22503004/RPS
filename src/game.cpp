# include "DxLib.h"

# include "game.hpp"
# include "gameimage.hpp"
# include "gamebet.hpp"
# include "gameselect.hpp"
# include "gameresult.hpp"
# include "gameplayer.hpp"
# include "gameother.hpp"
# include "click.hpp"


/* ------------------
	private
--------------------- */
void Game::InitGame(bool isInit) {

	// variant
	if (isInit) {
		player1->Init(names[0], initPoint);
		player2->Init(names[1], initPoint);
		round = 1;
		turn = 0;
	}


	// parent & child
	if (isInit) {
		parent = player1;
		child = player2;
	}
	else {
		if (parent == player1) {
			parent = player2;
			child = player1;
		}
		else {
			parent = player1;
			child = player2;
		}
	}
			

	// bet
	bet->ChangeBet(-999);
	bet->SetMaxBet(parent->GetPoint());
	oth->SetBet(-1);

	// round
	oth->SetRound(round);

	return;
}


int Game::BetTurn() {

	//draw
	Draw(0);

	// click
	if (click->IsClick()) {
		if (bet->ChangeOrGoToNext()) return 1;
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
		if (current->DecideHand(hover)) return (n+1);
	}

	return n;

}


int Game::FirstPlayerTurn() {

	return SelectTurn(1);
}


int Game::SecondPlayerTurn() {

	return SelectTurn(2);
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
			return 0;
		}
	}

	return 3;
}


void Game::Draw(int n) {

	ClearDrawScreen();

	player1->DrawPlayer();
	player2->DrawPlayer();
	oth->DrawOther();

	switch(n) {
		case 0:
			bet->DrawBet();
			break;

		case 1:
			img->DrawSelect();
			slc->DrawSelect(hover, turn, name);

			break;

		case 2:
			img->DrawResult(h1, h2);
			rsl->DrawResult(name);
			break;
	}

	ScreenFlip();

	return;
}

bool Game::TurnEnd(int n) {

	// if not end turn
	if (n == turn) return true;

	int m;
	bool isGameOver[2];
	switch (n) {
		case 0:
			// set bet
			m = bet->GetBet();
			oth->SetBet(m);

			// set next player	
			current = parent;
			name = current->GetName();

			break;

		case 1:
			// set next player
			current = child;
			name = current->GetName();

			break;

		case 2:
			// result
			h1 = parent->GetHand();
			h2 = child->GetHand();
			m = bet->GetBet();
			rsl->CalculateResult(h1, h2, m);

			// set variant
			name = parent->GetName();

			break;

		case 3:
			// change point
			m = rsl->GetDelta(0);
			isGameOver[0] = parent->ChangePoint(m);
			isGameOver[1] = child->ChangePoint(-m);

			// is point < 0 (= gameover) ?
			if (isGameOver[0] || isGameOver[1]) return false;

			// update variant
			InitGame(false);

			break;
	}

	return true;
}


/* ----------------
	public
------------------- */
// constructor & destructor
Game::Game() :
	initPoint(100),

	img(new GameImage),
	bet(new GameBet(initPoint)),
	slc(new GameSelect),
	rsl(new GameResult),
	player1(new GamePlayer(1)),
	player2(new GamePlayer(2)),
	oth(new GameOther),
	click(new Click),

	round(1),
	roundMax(3),
	turn(0)
{
	parent = player1;
	child = player2;
}

Game::~Game() {

	delete img;
	delete bet;
	delete slc;
	delete rsl;
	delete player1;
	delete player2;
	delete oth;
	delete click;
}



// function
int Game::game(const char* s[2], int p[2], int mode) {

	// init
	names[0] = s[0];
	names[1] = s[1];
	InitGame(true);

	// loop
	bool isLoop = true;

	while (isLoop) {

		switch (turn) {

			case 0:
				turn = BetTurn();
				TurnEnd(0);
				break;

			case 1:
				turn = FirstPlayerTurn();
				TurnEnd(1);
				break;
		
			case 2:
				turn = SecondPlayerTurn();
				TurnEnd(2);
				break;
		
			case 3:
				turn = ResultTurn();
				isLoop = TurnEnd(3);	// break loop if game over
				break;

			default:
				isLoop = false;
				break;
		}


		// other
		if (ProcessMessage() == -1) break;
		WaitTimer(1000/60);
	}

	// move result scene
	p[0] = player1->GetPoint();
	p[1] = player2->GetPoint();

	return 3;
}
