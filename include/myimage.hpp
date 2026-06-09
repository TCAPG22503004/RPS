# ifndef MYIMAGE
# define MYIMAGE

class MyImage {

	private:
		// png
		int hands[3];	// [rock, scissors, paper]

		// position
		int imagePos[3][2][2];	// [rock, scissors, paper] [min, max] [x, y]

		// function
		void LoadImages();
		void SetImagePos();

	public:
		void Init();
		void End();
		void DrawSelect();
		int CheckHover();
};

# endif
