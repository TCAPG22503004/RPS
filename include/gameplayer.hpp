# ifndef GAMEPLAYER
# define GAMEPLAYER

class GamePlayer {

	private:
		// player data
		const char* name;
		int point;
		int playerNumber;
		int hand;
	
		// drawing data
		int font;
		int white;
		int x, y, size, len;
		int pos[2];	// [xmin, ymin]

		// text
		const char* text;

		// function
		void SetPos();

	public:
		// constructor & destructor
		GamePlayer(int n, int p, const char* s);
		~GamePlayer();

		// function
		void DrawPlayer();
		bool DecideHand(int n);
		bool ChangePoint(int n);
		int GetHand();
		const char* GetName();
		int GetPoint();
		void InitPoint(int n);
};

# endif
