# ifndef MENU
# define MENU

class Menu {
	private:
		// drawing data
		int font, white, red, black;
		int x, y, size, otherSize;
		int boxSize[2];		// [width, height]
		int menuPos[3][2][2];	// [solo, local, global] [box1, box2]
		int clickPos[3][3][2];	// [solo, local, global] [button, box1, box2]
		int len[3];		// [solo, local, global]
		int describePos[2];	// [x, y]
		int titlePos[2];	// [x, y]
		int lenTitle;

		// text
		const char* menuText[3][2];	// [solo, local, global] [box1, box2]
		const char* button[3];		// [solo, local, global]
		const char* hover[3];		// [solo, local, global]
		const char* title;

		// other variant
		int inputHandle;
		char input[3][2][16];	// input srting
		int inputBox[2];		// which box is selected?
		int mode;			// game mode (solo or local or global)

		// function
		void SetPos();
		void InputString(int n, int m);
		void DrawInputString();
		void SetString();
		void Draw();
		bool isHover(int *n, int *m);
		int OnClick();
		void CopyString(char s1[16], char s2[16]);

	public:
		// constructor & destructor
		Menu();
		~Menu();


		// function
		int menu(char s[2][16], char r[16], int *m);
};

# endif
