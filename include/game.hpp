# ifndef GAME
# define GAME


// forward declaration
class GameImage;
class GameBet;
class GameSelect;
class GameResult;
class GamePlayer;
class GameOther;
class Click;


// main class
class Game {

	private:
		// variant
		int initPoint;
		int round, roundMax;
		int hover;
		int turn;
		int h1, h2;		// to Draw()
		const char* name;	// to Draw()

		// other class
		GameImage *img;
		GameBet *bet;
		GameSelect *slc;
		GameResult *rsl;
		GamePlayer *player1;
		GamePlayer *player2;
		GameOther *oth;
		Click *click;

		GamePlayer *parent, *child, *current;

		// function
		void InitGame(bool isInit);
		int BetTurn();
		int SelectTurn(int n);
		int FirstPlayerTurn();
		int SecondPlayerTurn();
		int ResultTurn();
		void Draw(int n);
		bool TurnEnd(int n);

	public:
		// constructor & destructor
		Game();
		~Game();

		// function
		int game();
};

# endif
