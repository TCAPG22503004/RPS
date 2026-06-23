# ifndef MENU
# define MENU

class Menu {
	private:
		// drawing data
		int font, white, red, black;
		int x, y, size, h;
		int boxSize[2];		// [width, height]
		int menuPos[3][2][2];	// [solo, local, global] [box1, box2]
		int clickPos[3][3][2];	// [solo, local, global] [button, box1, box2]
		int len[3];		// [solo, local, global]
		int describePos[2];	// [x, y]

		// text
		const char* menuText[3][2];	// [solo, local, global] [box1, box2]
		const char* button[3];		// [solo, local, global]
		const char* hover[3];		// [solo, local, global]

		// other variant
		int inputHandle;
		char input[3][2][16];	// input srting
		int mode;		// game mode (solo or local or global)

		// function
		void SetPos();
		void InputString(int n, int m);
		void Draw();
		bool isHover(int *n, int *m);
		int OnClick();

	public:
		// constructor & destructor
		Menu();
		~Menu();


		// function
		int menu(const char* s[2], const char* id, int *m);
};

# endif
