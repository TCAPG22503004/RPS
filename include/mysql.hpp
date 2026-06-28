# ifndef MYSQL_CLASS
# define MYSQL_CLASS

struct st_mysql;
struct st_mysql_res;

class MysqlClass {

	private:
		st_mysql* conn;
		st_mysql_res* result;

	public:
		// constructor & destructor
		MysqlClass();
		~MysqlClass();

		// function
		bool Connect();
		bool Insert(char name[16], char roomID[16]);
		char* Select(char name[16], char roomID[16], int n); 
		bool Update(char name[16], char roomID[16], const char* s, int n);
		bool Delete(char name[16], char roomID[16]);

		int CountExistRoomID(char roomID[16]);
		char* GetOtherPlayerName(char roomID[16]);
};

// memo (name, roomid, score, hand, bet)

# endif
