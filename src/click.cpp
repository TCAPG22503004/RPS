# include "DxLib.h"

# include "click.hpp"

/* -----------------
	private
-------------------- */



/* -----------------
	public
-------------------- */
Click::Click() :
	isHold(false)
{
}


bool Click::IsClick() {

	// start or remain click
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

		// is remaining?
		if (isHold) {
			return false;
		}

		else {
			isHold = true;
			return true;
		}
	}

	// end click
	else {
		isHold = false;
	}

	return false;
}
