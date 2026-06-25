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
		bool Insert(const char* name, const char* roomID);
		const char* Select(const char* name, const char* roomID, int n); 
		bool Update(const char* name, const char* roomID, const char* s, int n);
		bool Delete(const char* name, const char* roomID);

		int CountExistRoomID(const char* roomID);
};

// memo (name, roomid, score, hand, bet)

# endif
