# ifndef TITLE
# define TITLE

class Title {

	private:
		// drawing data
		int white, red;
		int x, y, size;
		int titleFont;
		int titlePos[2];	// [xmin, ymin]
		int buttonPos[2][2];	// [start, quit] [xmin, ymin]
		int len[2];		// [start, quit]

		// text
		const char* titleText;
		const char* button[2];	// [start, quit]

		// function
		void SetPos();
		void SetTitlePos();
		void SetButtonPos();
		void Draw();
		int PushedButton();

	public:
		// constructor
		Title();
		~Title();

		// function
		int title();
};

# endif
