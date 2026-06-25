# include <cstdio>

# include "mysql.h"

# include "mysql.hpp"

/* ----------------
	public
------------------- */
// constructor & destructor
MysqlClass::MysqlClass() {
	conn = mysql_init(NULL);
}

MysqlClass::~MysqlClass() {
	if (result != nullptr) mysql_free_result(result);
	mysql_close(conn);
}



// function
bool MysqlClass::Connect() {

	// set variant
	const char* ip = "192.168.0.8";
	const char* user = "GameMasterRPS";
	const char* password = "ReflectonPlayingStrategy";
	const char* database = "RPS";
	int port = 3306;

	int sslMode = 1;
	mysql_options(conn, MYSQL_OPT_SSL_MODE, &sslMode);

	// connect
	conn = mysql_real_connect(conn, ip, user, password, database, port, NULL, 0);

	return conn;
}


bool MysqlClass::Insert(const char* name, const char* roomID) {

	char query[256];
	snprintf(query, sizeof(query), "insert into data (name, roomID) values ('%s', '%s');", name, roomID);

	return (mysql_query(conn, query) == 0);
}


const char* MysqlClass::Select(const char* name, const char* roomID, int n) {

	char query[256];
	snprintf(query, sizeof(query), "select * from data where name = '%d' and roomID = '%d';", name, roomID);

	// read data
	if (mysql_query(conn, query) == 0) {

		MYSQL_RES* result = mysql_store_result(conn);

		// get data
		if (result != nullptr) {

			MYSQL_ROW row = mysql_fetch_row(result);

			if (row != nullptr) return row[n];
		}
	}

	// cannot read or get data
	const char* s = "Failed MySQL Select";
	return s;
}


bool MysqlClass::Update(const char* name, const char* roomID, const char* s, int n) {

	char query[256];
	snprintf(query, sizeof(query), "update data set %s = %d where name = '%s' and roomID = '%s';", s, n, name, roomID);

	if (mysql_query(conn, query) == 0) {

		// is update only 1 column?
		int rows = mysql_affected_rows(conn);
		return (rows == 1);
	}

	// failed
	return false;
}


bool MysqlClass::Delete(const char* name, const char* roomID) {

	char query[256];
	snprintf(query, sizeof(query), "delete from data where name = '%d' and roomID = '%d';", name, roomID);

	if (mysql_query(conn, query) == 0) {

		// is delete only 1 column?
		int rows = mysql_affected_rows(conn);
		return (rows == 1);
	}

	// failed
	return false;
}



int MysqlClass::CountExistRoomID(const char* roomID) {

	char query[256];
	snprintf(query, sizeof(query), "select * from data where roomID = '%d';", roomID);

	// read data
	if (mysql_query(conn, query) == 0) {

		MYSQL_RES* result = mysql_store_result(conn);

		// count
		if (result != nullptr) {
			int n = mysql_num_rows(result);
			return n;
		}
	}

	// cannot read data
	return -1;			
}
