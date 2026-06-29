# ifndef MYSQL_CLASS
# define MYSQL_CLASS

struct st_mysql;
struct st_mysql_res;

class MysqlClass {

	private:
		st_mysql* conn;

	public:
		// constructor & destructor
		MysqlClass();
		~MysqlClass();

		// function
		bool Connect();
		bool Insert(char name[16], char roomID[16]);
		bool Select(char name[16], char roomID[16], int n, char s[16]); 
		bool Update(char name[16], char roomID[16], const char* s, int n);
		bool Delete(char name[16], char roomID[16]);

		int CountExistRoomID(char roomID[16]);
		bool GetOtherPlayerName(char roomID[16], char s[16]);
};

// memo (name, roomid, hand, bet)

# endif
