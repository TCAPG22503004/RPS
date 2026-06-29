# include "DxLib.h"

# include "game.hpp"
# include "gameimage.hpp"
# include "gamebet.hpp"
# include "gameselect.hpp"
# include "gameresult.hpp"
# include "gameplayer.hpp"
# include "gameother.hpp"
# include "gameonline.hpp"
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


	// GamePlayer Class
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
	current = parent;
	name = current->GetName();
			

	// bet
	bet->ChangeBet(-999);
	bet->SetMaxBet(parent->GetPoint());
	oth->SetBet(-1);

	// round
	oth->SetRound(round);

	return;
}


int Game::BetTurn() {

	// player turn
	if (mode == 1 || current == myself) {

		//draw
		Draw(0);
	
		// click
		if (click->IsClick()) {
			if (bet->ChangeOrGoToNext()) {

				// online
				if (mode == 2) onl->SetData(name, room, "bet", bet->GetBet());

				// go to next phase(= select)
				return 1;
			}
		}
	}

	// cpu turn
	else if (mode == 0) {
		
		// draw
		Draw(-1);

		// random
		bet->SetBetRandom();
		return 1;
	}

	// other player turn
	else {
		// draw
		Draw(-1);
		onl->DrawRound();

		// wait to decide other player
		int n = onl->WaitRound(name, room, 3, false);
		if (n < 1) return -1;

		// decided
		bet->SetBet(n);
		
		return 1;
	}

	return 0;

}


int Game::SelectTurn(int n) {

	// player turn
	if (mode == 1 || current == myself) {

		// get mouse position
		hover = img->CheckHover();
	
		// draw
		Draw(1);
	
		// after choice
		if (click->IsClick()) {
			if (current->DecideHand(hover)) {

				// online
				if (mode == 2) onl->SetData(name, room, "hand", current->GetHand());

				// go to next phase(= player2 or result)
				return (n+1);
			}
		}
	
		return n;
	}

	// cpu turn
	else if (mode == 0) {
		
		// draw
		Draw(-2);

		// random
		current->DecideHandRandom();
		return (n+1);
	}

	// other player turn
	else {
		// draw
		Draw(-2);
		onl->DrawRound();

		// wait to decide other player
		int hand = onl->WaitRound(name, room, 2, false);
		if (hand < 0) return -1;

		// decided
		current->DecideHand(hand);

		return (n+1);
	}

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
		
		// online
		if (mode == 2) {
			onl->DrawRound();
			onl->SetData(myName, room, "bet", -1);
			onl->SetData(myName, room, "hand", -1);
			int n = onl->WaitRound(otherName, room, 3, true);
		}

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
		// bet
		case 0:
			bet->DrawBet();
			break;

		// select
		case 1:
			img->DrawSelect();
			slc->DrawSelect(hover, turn, name);

			break;

		// result
		case 2:
			img->DrawResult(h1, h2);
			rsl->DrawResult(name);
			break;

		// other bet
		case -1:
			bet->DrawBetWait();
			break;

		// other select
		case -2:
			slc->DrawSelectWait();
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
	round(1),
	roundMax(3),
	turn(0),

	img(new GameImage),
	bet(new GameBet(initPoint)),
	slc(new GameSelect),
	rsl(new GameResult),
	player1(new GamePlayer(1)),
	player2(new GamePlayer(2)),
	oth(new GameOther(roundMax)),
	onl(new GameOnline),
	click(new Click)

{
	parent = player1;
	child = player2;
}

Game::~Game() {

	// online
	onl->DeleteUser(names, room);

	delete img;
	delete bet;
	delete slc;
	delete rsl;
	delete player1;
	delete player2;
	delete oth;
	delete onl;
	delete click;
}



// function
int Game::game(char s[2][16], char r[16], int p[2], int m) {

	// ---- online room function begin ----
	bool isPlayer1 = true;
	if (m == 2) {
		int flag = onl->InitRoom(s, r, &isPlayer1);
		if (flag != 0) {
			if (flag == -2) onl->DrawError(0);	// used room id
			else if (flag == -3) onl->DrawError(1);	// used name

			WaitTimer(3000);
			return 1;
		}
		strcpy(room, r);
	}
	// ---- online room function end ----

	// init
	strcpy(names[0], s[0]);
	strcpy(names[1], s[1]);
	mode = m;
	InitGame(true);

	// set player
	current = parent;
	name = current->GetName();

	// ---- online ----
	myself = (isPlayer1) ? player1 : player2;
	myName = myself->GetName();

	GamePlayer* other;
	other = (isPlayer1) ? player2 : player1;
	otherName = other->GetName();
	// ---- online ----

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

	// online
	onl->DeleteUser(names, room);

	return 3;
}
