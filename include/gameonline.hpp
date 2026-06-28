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
		bool isConnect;
		static char* other;

		// function
		void SetPos();
		void SetRoomPos();
		void SetRoundPos();
		void SetButtonPos();

		void DrawRoom(char room[16]);
		void DrawRound();
		bool IsPushButton();

	public:
		// constructor & destructor
		GameOnline();
		~GameOnline();

		// function
		int InitRoom(char name[2][16], char room[16], bool *isPlayer1);
};

# endif
