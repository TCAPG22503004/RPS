# include "DxLib.h"

# include "gameimage.hpp"


/* -----------------
	private
-------------------- */
void GameImage::LoadImages() {

	hands[0] = LoadGraph("../img/janken_gu.png");
	hands[1] = LoadGraph("../img/janken_choki.png");
	hands[2] = LoadGraph("../img/janken_pa.png");
	
	return;
}


void GameImage::SetImagePos() {

	// get screen size
	int x, y;
	GetScreenState(&x, &y, NULL);

	// set image size (now: 1/8 scale per screen x)
	int size = x / 8;

	// set position
	// [rock, scissors, paper]
	for (int i = 0; i < 3; i++) {
		imagePos[i][0][0] = (x/4) * (i+1) - (size/2);	// xmin
		imagePos[i][0][1] = (y/2) - (size/2);		// ymin
		imagePos[i][1][0] = imagePos[i][0][0] + size;	// xmax
		imagePos[i][1][1] = imagePos[i][0][1] + size;	// ymax
	}

	return;
}




/* ----------------
	public
------------------- */
void GameImage::Init() {

	LoadImages();
	SetImagePos();

	return;
}

void GameImage::End() {

	// dxlib function
	InitGraph();

	return;
}


int GameImage::CheckHover() {

	// get mouse position
	int x, y;
	GetMousePoint(&x, &y);


	// [rock, scissors, paper]
	for (int i = 0; i < 3; i++) {

		int xmin = imagePos[i][0][0];
		int ymin = imagePos[i][0][1];
		int xmax = imagePos[i][1][0];
		int ymax = imagePos[i][1][1];

		bool insideX = ((x >= xmin) && (x <= xmax));
		bool insideY = ((y >= ymin) && (y <= ymax));

		// hovering
		if (insideX && insideY) return i;
	}

	// not hover
	return -1;
}


void GameImage::DrawSelect() {

	// [rock, scissors, paper]
	for (int i = 0; i < 3; i++) {
	
		int xmin = imagePos[i][0][0];
		int ymin = imagePos[i][0][1];
		int xmax = imagePos[i][1][0];
		int ymax = imagePos[i][1][1];
		int hand = hands[i];

		DrawExtendGraph(xmin, ymin, xmax, ymax, hand, TRUE);
	}

	return;
}


void GameImage::DrawResult(int n, int m) {
	
	int xmin = imagePos[0][0][0];
	int ymin = imagePos[0][0][1];
	int xmax = imagePos[0][1][0];
	int ymax = imagePos[0][1][1];
	int hand = hands[n];

	DrawExtendGraph(xmin, ymin, xmax, ymax, hand, TRUE);
	
	xmin = imagePos[2][0][0];
	ymin = imagePos[2][0][1];
	xmax = imagePos[2][1][0];
	ymax = imagePos[2][1][1];
	hand = hands[m];

	DrawExtendGraph(xmin, ymin, xmax, ymax, hand, TRUE);


	return;
}
