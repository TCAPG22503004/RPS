# ifndef GAMEPLAYER
# define GAMEPLAYER

class GamePlayer {

	private:
		// player data
		const char* name[2];	// [player1, player2]
		int point[2];		// [player1, player2]
	
		// drawing data
		int font;
		int white;
		int size;
		int pos[2][2];		// [player1, player2] [xmin, ymin]

		// text
		const char* text;

		// function
		void SetPos();

	public:
		// constructor & destructor
		GamePlayer();
		~GamePlayer();

		// function
		void DrawPlayer();
};

# endif
