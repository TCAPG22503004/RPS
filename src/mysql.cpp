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


bool MysqlClass::Insert(char name[16], char roomID[16]) {

	char query[256];
	snprintf(query, sizeof(query), "insert into data (name, roomID, hand, bet) values ('%s', '%s', -1, -1);", name, roomID);

	return (mysql_query(conn, query) == 0);
}


bool MysqlClass::Select(char name[16], char roomID[16], int n, char s[16]) {

	char query[256];
	snprintf(query, sizeof(query), "select * from data where name = '%s' and roomID = '%s';", name, roomID);

	// read data
	if (mysql_query(conn, query) == 0) {

		st_mysql_res* result = mysql_store_result(conn);

		// get data
		if (result != nullptr) {

			MYSQL_ROW row = mysql_fetch_row(result);

			if (row != nullptr) {
				for (int i = 0; i < 16; i++) {
					s[i] = row[n][i];
				}
				mysql_free_result(result);

				return true;
			}
		}
	}

	// cannot read or get data
	return false;
}


bool MysqlClass::Update(char name[16], char roomID[16], const char* s, int n) {

	char query[256];
	snprintf(query, sizeof(query), "update data set %s = %d where name = '%s' and roomID = '%s';", s, n, name, roomID);

	return (mysql_query(conn, query) == 0);
}


bool MysqlClass::Delete(char name[16], char roomID[16]) {

	char query[256];
	snprintf(query, sizeof(query), "delete from data where name = '%s' and roomID = '%s';", name, roomID);

	return (mysql_query(conn, query) == 0);
}



// other

int MysqlClass::CountExistRoomID(char roomID[16]) {

	char query[256];
	snprintf(query, sizeof(query), "select * from data where roomID = '%s';", roomID);

	// read data
	if (mysql_query(conn, query) == 0) {

		st_mysql_res* result = mysql_store_result(conn);

		// count
		if (result != nullptr) {
			int n = mysql_num_rows(result);
			mysql_free_result(result);

			return n;
		}
	}

	// cannot read data
	return -1;			
}


bool MysqlClass::GetPlayerName(char roomID[16], char s[16]) {

	char query[256];
	snprintf(query, sizeof(query), "select * from data where roomID = '%s';", roomID);

	// read data
	if (mysql_query(conn, query) == 0) {

		st_mysql_res* result = mysql_store_result(conn);

		// get data
		if (result != nullptr) {

			if (mysql_num_rows(result) == 2) mysql_data_seek(result, 1);

			// get data
			MYSQL_ROW row = mysql_fetch_row(result);

			if (row != nullptr) {
				for (int i = 0; i < 16; i++) {
					s[i] = row[0][i];
				}
				mysql_free_result(result);

				return true;
			}
		}
	}

	// cannot read or get data
	return false;
}

