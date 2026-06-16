# ifndef GAMERESULT
# define GAMERESULT

class GameResult {

	private:
		// drawing data
		int white;
		int x, y, size;
		int textResultPos[3][2];	// [draw, lose, win] [xmin, ymin]

		// text
		const char* textResult[3];	// [draw, lose, win] 

		// function
		void SetTextPos();
		void SetResultPos();

	public:
		// constructor
		GameResult();

		// function
		void DrawResult(int n, int m);
};

# endif
