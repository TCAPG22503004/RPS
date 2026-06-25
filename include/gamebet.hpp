# ifndef GAMEBET
# define GAMEBET

class GameBet {

	private:
		// bet data
		int bet;
		int maxBet;
	
		// drawing data
		int white;
		int red;
		int x, y, size;
		int textPos[2];		// [xmin, ymin]
		int numPos[2];		// [xmin, ymin]
		int buttonPos[4][2];	// [-10, -1, +1, +10] [xmin, ymin]
		int nextPos[2];		// [xmin, ymin]
		int waitPos[2];		// [xmin, ymin]
		int lenButton[4];	// length of [-10, -1, +1, +10]
		int lenNext;		// length of next

		// text
		const char* text;	// describe
		const char* button[4];	// [-10, -1, +1, +10]
		const char* next;	// go to next(player1) turn
		const char* wait;	// wait other player

		// function
		void SetPos();
		void SetTextPos();
		void SetNumPos();
		void SetButtonPos();
		void SetNextPos();
		void SetWaitPos();

	public:
		// constructor
		GameBet(int p);

		// function
		void DrawBet();
		void DrawBetWait();
		bool ChangeOrGoToNext();
		void ChangeBet(int n);
		void SetMaxBet(int n);
		void SetBetRandom();
		int GetBet();
};

# endif
