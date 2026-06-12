# ifndef GAME
# define GAME


// forward declaration
class GameImage;
class GameString;
class Click;


// main class
class Game {

	private:
		// variant
		int roundMax;
		int hover;
		int select[2];	// player1, player2

		// other class
		GameImage *img;
		GameString *str;
		Click *click;

		// function
		int SelectTurn(int n, const char* name, int point);
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
