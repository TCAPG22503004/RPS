# ifndef GAMESELECT
# define GAMESELECT

class GameSelect {

	private:
	
		// drawing data
		int white;
		int x, y, size;
		int textHoverPos[3][2];		// [rock, scissors, paper] [xmin, ymin]
		int textPlayerPos[2];

		// text
		const char* textHover[3];	// [rock, scissors, paper]
		const char* textPlayer;
		const char* textTurn[2];	// [parent. child]

		// function
		void SetTextPos();
		void SetHoverPos();
		void SetPlayerPos();

	public:
		// constructor
		GameSelect();

		// function
		void DrawSelect(int hover, int n, const char* name);
};

# endif
