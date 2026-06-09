# ifndef MYSTRING
# define MYSTRING

class MyString {

	private:
	
		// drawing data
		int font;
		int white;
		int textPos[3][2];	// [rock, scissors, paper] [xmin, ymin]

		// text
		const char* textHover[3];

		// function
		void SetTextPos();

	public:
		void Init();
		void End();
		void DrawSelect(int hover);
};

# endif
