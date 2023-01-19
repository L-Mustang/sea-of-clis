#include <goods.h>
#include <harbor.h>
#include <filesystem/sqlite_3.h>

#include <sqlite3.h>


namespace Soc::Filesystem
{
	Sqlite_3::Sqlite_3(const std::filesystem::path& db) : m_db(nullptr)
	{
		if (sqlite3_open_v2(db.string().c_str(), &m_db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
		{
			throw std::runtime_error(sqlite3_errmsg(m_db));
		}
	}

	Sqlite_3::~Sqlite_3()
	{
		sqlite3_close(m_db);
	}

	std::map<int, std::shared_ptr<Harbor>> Sqlite_3::harbors()
	{
		auto cb = [](void* res, int col_count, char** records, char** col_names)
		{
			const auto goods = static_cast<std::map<int, std::shared_ptr<Harbor>>*>(res);
			goods->emplace(
				std::stoi(std::string{ records[0] }),
				std::make_shared<Harbor>(
				std::stoi(std::string{ records[0] }),
				std::string{ records[1] }
			));
			return 0;
		};
		const std::string query = "SELECT * FROM havens";
		std::map<int, std::shared_ptr<Harbor>> res;
		get_results(query, cb, &res);
		return res;
	}

	std::map<int, Goods> Sqlite_3::goods(int harbor_id)
	{
		auto cb = [](void* res, int col_count, char** records, char** col_names)
		{
			const auto goods = static_cast<std::map<int, Goods>*>(res);
			goods->emplace(
				std::stoi(std::string{ records[0] }), 
				Goods{ std::stoi(std::string{ records[0]}),
				std::string{ records[1] },
				std::stoi(std::string{ records[2] }),
				std::stoi(std::string{ records[3] }),
				std::stoi(std::string{ records[4] }),
				std::stoi(std::string{ records[5] })
				});
			return 0;
		};
		const std::string query = std::format(
			"SELECT id, goed, min_goed, max_goed, min_prijs, max_prijs "
			"FROM havens_goederen "
			"JOIN goederen ON havens_goederen.goed_id == goederen.id "
			"WHERE havens_goederen.haven_id = {}",
			harbor_id);
		std::map<int, Goods> res;
		get_results(query, cb, &res);
		return res;
	}

}
