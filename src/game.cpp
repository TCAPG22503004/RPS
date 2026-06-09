# include <string.h>

# include "DxLib.h"

# include "game.hpp"
# include "myimage.hpp"
# include "mystring.hpp"


/* ------------------
	private
--------------------- */



/* ----------------
	public
------------------- */

int Game::test() {

	MyImage img;
	img.Init();

	MyString str;
	str.Init();

	// debug
	int white = GetColor(255, 255, 255);

	while (true) {

		hover = img.CheckHover();
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) select = hover;

		ClearDrawScreen();

		DrawFormatString(0, 0, white, "%d", select);	// debug
		img.DrawSelect();
		str.DrawSelect(hover);

		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (ProcessMessage() == -1) break;
		WaitTimer(1000/60);
	}

	img.End();
	str.End();

	return -1;
}
