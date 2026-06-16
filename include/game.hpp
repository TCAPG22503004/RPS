# ifndef GAME
# define GAME


// forward declaration
class GameImage;
class GameSelect;
class GameResult;
class Click;


// main class
class Game {

	private:
		// variant
		int round, roundMax;
		int hover;
		int select[2];	// player1, player2

		// other class
		GameImage *img;
		GameSelect *slc;
		GameResult *rsl;
		Click *click;

		// function
		int SelectTurn(int n);
		int FirstPlayerTurn();
		int SecondPlayerTurn();
		int ResultTurn();

	public:
		// constructor & destructor
		Game();
		~Game();

		// function
		int test();

};

# endif
