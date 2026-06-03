# ifndef GAME
# define GAME

class Game {

	private:
		// image
		int gu, choki, pa;
		int leftPos[2][2];
		int centerPos[2][2];
		int rightPos[2][2];

		// text
		int font;
		int white;
		int hover;
		int select;
		int mousePos[2];
		int txtPos[3][2];
		const char* hoverGu;
		const char* hoverChoki;
		const char* hoverPa;

		// etc
		int x, y;

		// function
		void Init();
		void SetImagePos(int pos[2][2], int n);
		void SetTextPos(const char* s, int n);
		void SetHover();
		void SetSelect();
		void Draw();

	public:
		int test();

};

# endif
