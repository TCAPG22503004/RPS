# ifndef GAMEONLINE
# define GAMEONLINE

// forward declaration
class MysqlClass;

class GameOnline {

	private:
	
		// drawing data
		int white, red;
		int x, y, size;
		int textRoomPos[2];	// [x, y]
		int textRoundPos[2];	// [x, y]
		int buttonPos[2];	// [x, y]
		int lenButton;

		// text
		const char* textRoom;
		const char* textRound;
		const char* button;

		// other
		MysqlClass *sql;

		// function
		void SetPos();
		void SetRoomPos();
		void SetRoundPos();
		void SetButtonPos();

	public:
		// constructor & destructor
		GameOnline();
		~GameOnline();

		// function
		void DrawRoom(char room[16]);
		void DrawRound();
		bool IsBack();

		int MakeRoom(char name[16], char room[16]);
};

# endif
