# ifndef GAMEIMAGE
# define GAMEIMAGE

class GameImage {

	private:
		// png
		int hands[3];	// [rock, scissors, paper]

		// position
		int imagePos[3][2][2];	// [rock, scissors, paper] [min, max] [x, y]

		// function
		void LoadImages();
		void SetImagePos();

	public:
		// constructor & destructor
		GameImage();
		~GameImage();

		// function
		int CheckHover();
		void DrawSelect();
		void DrawResult(int n, int m);
};

# endif
