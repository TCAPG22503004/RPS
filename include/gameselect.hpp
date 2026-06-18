# ifndef GAMESELECT
# define GAMESELECT

class GameSelect {

	private:
	
		// drawing data
		int white;
		int x, y, size;
		int textHoverPos[3][2];		// [rock, scissors, paper] [xmin, ymin]
		int textInfoPos[2][2];		// [round, bet] [xmin, ymin]

		// text
		const char* textHover[3];	// [rock, scissors, paper]
		const char* textInfo[2];	// [round, bet]

		// function
		void SetTextPos();
		void SetHoverPos();
		void SetInfoPos();

	public:
		// constructor
		GameSelect();

		// function
		void DrawSelect(int hover, int round, int bet);
};

# endif
