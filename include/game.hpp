# ifndef GAME
# define GAME


// forward declaration
class GameImage;
class GameBet;
class GameSelect;
class GameResult;
class GamePlayer;
class Click;


// main class
class Game {

	private:
		// variant
		int round, roundMax;
		int hover;
		int select[2];	// player1, player2
		int nBet;

		// other class
		GameImage *img;
		GameBet *bet;
		GameSelect *slc;
		GameResult *rsl;
		GamePlayer *ply;
		Click *click;

		// function
		int BetTurn();
		int SelectTurn(int n);
		int FirstPlayerTurn();
		int SecondPlayerTurn();
		int ResultTurn();
		void Draw(int n);

	public:
		// constructor & destructor
		Game();
		~Game();

		// function
		int test();

};

# endif
