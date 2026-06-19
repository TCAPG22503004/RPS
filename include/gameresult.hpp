# ifndef GAMERESULT
# define GAMERESULT

class GameResult {

	private:
		// variant
		int result, bet, bonus, delta;

		// drawing data
		int white;
		int x, y, size;
		int textResultPos[2];	// [xmin, ymin]
		int textInfoPos[2];	// [xmin, ymin]

		// text
		const char* textResult;
		const char* textList[3];	// [draw, lose, win]
		const char* textInfo;

		// function
		void SetTextPos();
		void SetResultPos();
		void SetInfoPos();

	public:
		// constructor
		GameResult();

		// function
		void DrawResult(const char* name);
		void CalculateResult(int n, int m, int l);
		int GetDelta(int n);
};

# endif
