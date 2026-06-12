# ifndef GAMESTRING
# define GAMESTRING

class GameString {

	private:
	
		// drawing data
		int font;
		int white;
		int x, y, size;
		int textHoverPos[3][2];		// [rock, scissors, paper] [xmin, ymin]
		int textResultPos[3][2];	// [draw, lose, win] [xmin, ymin]
		int textOtherPos[4][2];		// [player, playerNumber, bet, betAmount] [xmin, ymin]

		// text
		const char* textHover[3];
		const char* textResult[3];
		const char* textOther[3];

		// function
		void SetTextPos();
		void SetHoverAndResultPos();
		void SetOtherPos();
		void SetCenter(const char* s, int pos[2]);

	public:
		// constructor & destructor
		GameString();
		~GameString();

		// function
		void DrawSelect(int hover, const char* name, int n);
		void DrawResult(int n, int m);
};

# endif
