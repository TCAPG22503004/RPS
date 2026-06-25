# ifndef RESULT
# define RESULT

class Result {

	private:
		// drawing data
		int white, red;
		int x, y, size;
		int resultPos[3][2];	// [txt, player1, player2] [xmin, ymin]
		int buttonPos[2][2];	// [retry, back] [xmin, ymin]
		int len[2];		// [retry, back]

		// text
		const char* resultText[3];	// [txt, player1, player2]
		const char* button[2];		// [retry, back]

		// player
		const char* name[2];	// [player1, player2]
		int point[2];		// [player1, player2]

		// function
		void SetPos();
		void SetResultPos();
		void SetButtonPos();
		void Draw();
		int PushedButton();

	public:
		// constructor
		Result();

		// function
		int result(const char* s[2], int p[2]);
};

# endif
