# ifndef GAMEOTHER
# define GAMEOTHER

class GameOther {

	private:
		// variant
		int round, roundMax;
		int bet;
	
		// drawing data
		int font;
		int white;
		int size;
		int pos[2][2];		// [round, bet] [xmin, ymin]

		// text
		const char* text[2];	// [round, bet]
		const char* textNotBet;

		// function
		void SetPos();

	public:
		// constructor
		GameOther(int n);

		// function
		void DrawOther();
		void SetRound(int n);
		void SetBet(int n);
};

# endif
