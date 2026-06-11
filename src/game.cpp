# include <string.h>

# include "DxLib.h"

# include "game.hpp"
# include "gameimage.hpp"
# include "gamestring.hpp"


/* ------------------
	private
--------------------- */



/* ----------------
	public
------------------- */
// constructor & destructor
Game::Game() :
	img(new GameImage),
	str(new GameString)
{
	img->Init();
	str->Init();
}

Game::~Game() {

	img->End();
	delete img;

	str->End();
	delete str;
}



// function
int Game::test() {

	int phase = 0;	// loop (player1, player2, result)

	while (true) {

		switch (phase) {

			/* -------------------
				player1
			---------------------- */
			case 0:
				// get mouse position
				hover = img->CheckHover();
		
				// draw
				ClearDrawScreen();
		
				img->DrawSelect();
				str->DrawSelect(hover);
		
				ScreenFlip();
		
				// after choice
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
					select[0] = hover;
					if (select[0] != -1) phase++;
				}

				break;
		
			/* --------------------
				player2
			----------------------- */
			case 1:
				select[1] = GetRand(2);

				// draw
				ClearDrawScreen();

				ScreenFlip();


				// next turn
//				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) phase++;
				phase++;

				break;

		
			/* -----------------
				result
			-------------------- */
			case 2:

				// draw
				ClearDrawScreen();

				img->DrawResult(select[0], select[1]);
				str->DrawResult(select[0], select[1]);

				ScreenFlip();


				// next turn
//				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) phase = 0;
				if (CheckHitKey(KEY_INPUT_SPACE) == 1) phase = 0;

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
