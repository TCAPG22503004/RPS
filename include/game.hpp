# ifndef GAME
# define GAME


// forward declaration
class GameImage;
class GameBet;
class GameSelect;
class GameResult;
class GamePlayer;
class GameOther;
class GameOnline;
class Click;


// main class
class Game {

	private:
		// variant
		int initPoint;
		int round, roundMax;
		int hover;
		int turn;
		int mode;
		int h1, h2;		// to Draw()
		char* name;		// to Draw(), online
		char names[2][16];	// to InitGame(), online
		char room[16];		// to online
		char* myName;		// to online
		char* otherName;	// to online

		// other class
		GameImage *img;
		GameBet *bet;
		GameSelect *slc;
		GameResult *rsl;
		GamePlayer *player1;
		GamePlayer *player2;
		GameOther *oth;
		GameOnline *onl;
		Click *click;

		GamePlayer *parent, *child, *current, *myself;

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
		int game(char s[2][16], char room[16], int point[2], int m);
};

# endif
