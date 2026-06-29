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
		char other[16];

		// function
		void SetPos();
		void SetRoomPos();
		void SetRoundPos();
		void SetButtonPos();
		bool IsPushButton();
		void DrawRoom(char room[16]);

	public:
		// constructor & destructor
		GameOnline();
		~GameOnline();

		// function
		void DrawError(int n);
		void DrawRound();
		int InitRoom(char names[2][16], char room[16], bool *isPlayer1);
		int WaitRound(char name[16], char room[16], int n, bool isTurnEnd);
		int GetData(char name[16], char room[16], int n);
		void SetData(char name[16], char room[16], const char* s, int n);
		int DeleteUser(char names[2][16], char room[16]);
};

# endif
