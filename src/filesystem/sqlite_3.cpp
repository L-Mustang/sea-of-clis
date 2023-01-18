#include <goods.h>
#include <harbor.h>
#include <filesystem/sqlite_3.h>
#include <random/random.h>

#include <sqlite3.h>


namespace Soc::Filesystem
{
	Sqlite_3::Sqlite_3(const std::filesystem::path& db)
	{
		if (sqlite3_open_v2(db.string().c_str(), &m_db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
		{
			throw std::runtime_error(sqlite3_errmsg(m_db));
		}
	}

	Sqlite_3::~Sqlite_3()
	{
		try
		{
			if (sqlite3_close(m_db) != SQLITE_OK)
			{
				throw std::runtime_error(sqlite3_errmsg(m_db));
			}
		}
		catch (std::exception& e)
		{
			// TODO Write to logger
			std::cerr << e.what() << std::endl;
		}
	}

	std::vector<std::shared_ptr<Harbor>> Sqlite_3::harbors()
	{
		return std::vector<std::shared_ptr<Harbor>>{};
	}

	std::shared_ptr<Harbor> Sqlite_3::harbor(int id)
	{
		auto cb = [](void* res, int col_count, char** records, char** col_names)
		{
			const auto harbor = static_cast<Harbor*>(res);
			harbor->id(std::stoi(std::string{records[0]}));
			harbor->harbor(std::string{records[1]});
			return 0;
		};

		const std::string query = std::format("SELECT * FROM havens WHERE id = {}", id);
		char* err = nullptr;
		const auto harbor = new Harbor{};
		sqlite3_exec(m_db, query.c_str(), cb, harbor, &err);
		sqlite3_free(err);
		return std::make_shared<Harbor>(*harbor);
	}

	std::vector<std::shared_ptr<Goods>> Sqlite_3::goods(int harbor_id)
	{
		auto cb = [](void* res, int col_count, char* records[], char* col_names[])
		{
			const auto goods = static_cast<std::vector<std::shared_ptr<Goods>>*>(res);
			goods->push_back(std::make_shared<Goods>(

				));
			return 0;
		};
		const std::string query = std::format(
			"SELECT id, goed, min_goed, max_goed, min_prijs, max_prijs"
			"FROM havens_goederen"
			"JOIN goederen on havens_goederen.goed_id == goederen.id"
			"WHERE havens_goederen.haven_id = {}",
			harbor_id);
		std::vector<std::shared_ptr<Goods>> goods;
		char *err = nullptr;
		sqlite3_exec(m_db, query.c_str(), cb, &goods, &err);
		sqlite3_free(err);
		return std::vector<std::shared_ptr<Goods>>{};
	}
}
