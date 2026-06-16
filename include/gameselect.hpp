# ifndef GAMESELECT
# define GAMESELECT

class GameSelect {

	private:
	
		// drawing data
		int white;
		int x, y, size;
		int textHoverPos[3][2];		// [rock, scissors, paper] [xmin, ymin]
		int textInfoPos[4][2];		// [round, bet, player1, player2] [xmin, ymin]

		// text
		const char* textHover[3];	// [rock, scissors, paper]
		const char* textInfo[4];	// [round, bet, player1, player2]

		// function
		void SetTextPos();
		void SetHoverPos();
		void SetInfoPos();

	public:
		// constructor
		GameSelect();

		// function
		void DrawSelect(int hover, int round, int bet, bool is1st, const char* name[2], int point[2]);
};

# endif
