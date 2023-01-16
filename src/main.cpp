int main()
{
	sqlite3* db = nullptr;
	if (sqlite3_open("db/handelsschepen.db", &db) != SQLITE_OK) {
		sqlite3_close(db);
		std::cerr << "error opening database file\n";
	}

	sqlite3_stmt* stmt = nullptr;
	const char* query = "SELECT id, bijzonderheid FROM bijzonderheden";
	if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
		std::cerr << sqlite3_errmsg(db) << std::endl;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		std::string desc = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		std::cout << desc << std::endl;
	}

	std::cout << "tested\n";

	return EXIT_SUCCESS;
}
