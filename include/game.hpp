# ifndef GAME
# define GAME


// forward declaration
class GameImage;
class GameString;


// main class
class Game {

	private:
		// variant
		int hover;
		int select[2];	// player1, player2

		// other class
		GameImage *img;
		GameString *str;

	public:
		// constructor & destructor
		Game();
		~Game();

		// function
		void Init();
		void End();
		int test();

};

# endif
