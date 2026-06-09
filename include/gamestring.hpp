# ifndef GAMESTRING
# define GAMESTRING

class GameString {

	private:
	
		// drawing data
		int font;
		int white;
		int textHoverPos[3][2];		// [rock, scissors, paper] [xmin, ymin]
		int textResultPos[3][2];	// [draw, lose, win] [xmin, ymin]

		// text
		const char* textHover[3];
		const char* textResult[3];

		// function
		void SetTextPos();

	public:
		void Init();
		void End();
		void DrawSelect(int hover);
		void DrawResult(int n, int m);
};

# endif
