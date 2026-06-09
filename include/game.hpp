# ifndef GAME
# define GAME

class Game {

	private:

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
		void SetTextPos(const char* s, int n);
		void SetHover();
		void SetSelect();
		void Draw();

	public:
		int test();

};

# endif
