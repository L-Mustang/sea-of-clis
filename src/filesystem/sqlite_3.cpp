#include <filesystem/sqlite_3.h>

#include <goods.h>
#include <harbor.h>
#include <ship.h>
#include <ship_small.h>
#include <ship_type.h>

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

	std::map<int, std::shared_ptr<Harbor>> Sqlite_3::harbors() const
	{
		auto cb = [](void* res, [[maybe_unused]] int col_count, char** records, [[maybe_unused]] char** col_names)
		{
			const auto goods = static_cast<std::map<int, std::shared_ptr<Harbor>>*>(res);
			goods->emplace(
				std::stoi(std::string{records[0]}),
				std::make_shared<Harbor>(
					std::stoi(std::string{records[0]}),
					std::string{records[1]}
				));
			return 0;
		};
		const std::string query = "SELECT * FROM havens";
		std::map<int, std::shared_ptr<Harbor>> res;
		exec_query(query, cb, &res);
		return res;
	}

	std::map<int, std::shared_ptr<Goods>> Sqlite_3::goods(const int harbor_id) const
	{
		auto cb = [](void* res, [[maybe_unused]] int col_count, char** records, [[maybe_unused]] char** col_names)
		{
			const auto goods = static_cast<std::map<int, std::shared_ptr<Goods>>*>(res);
			goods->emplace(
				std::stoi(std::string{records[0]}),
				std::make_shared<Goods>(std::stoi(std::string{records[0]}),
				                        std::string{records[1]},
				                        std::stoi(std::string{records[2]}),
				                        std::stoi(std::string{records[3]}),
				                        std::stoi(std::string{records[4]}),
				                        std::stoi(std::string{records[5]})
				));
			return 0;
		};
		const std::string query = std::format(
			"SELECT id, goed, min_goed, max_goed, min_prijs, max_prijs "
			"FROM havens_goederen "
			"JOIN goederen ON havens_goederen.goed_id == goederen.id "
			"WHERE havens_goederen.haven_id = {}",
			harbor_id);
		std::map<int, std::shared_ptr<Goods>> res;
		exec_query(query, cb, &res);
		return res;
	}

	std::map<int, std::shared_ptr<Ship>> Sqlite_3::ships() const
	{
		std::map<int, std::shared_ptr<Ship>> ships;
		const std::string query = "SELECT * FROM schepen";

		auto cb = [&](sqlite3_stmt* stmt)
		{
			const int id = sqlite3_column_int(stmt, 0);
			const std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			const int price = sqlite3_column_int(stmt, 2);
			const int cargo_max = sqlite3_column_int(stmt, 3);
			const int cannons_max = sqlite3_column_int(stmt, 4);
			const int hp = sqlite3_column_int(stmt, 5);
			auto weight_class = Ship_type::normal;
			const std::set<std::string> pec = peculiarities(id);

			if (pec.contains("licht"))
			{
				weight_class = Ship_type::light;
			}
			else if (pec.contains("log"))
			{
				weight_class = Ship_type::heavy;
			}

			if (pec.contains("klein"))
			{
				ships.emplace(id, std::make_shared<Ship_small>(
					              id, type, price, cargo_max, cannons_max, hp, weight_class
				              ));
			}
			else
			{
				ships.emplace(id, std::make_shared<Ship>(
					              id, type, price, cargo_max, cannons_max, hp, weight_class
				              ));
			}
		};

		exec_query_ext(query, cb);
		return ships;
	}

	void Sqlite_3::harbors_distances(const int harbor_id, std::map<int, std::shared_ptr<Harbor>>& harbors) const
	{
		auto cb = [](void* res, [[maybe_unused]] int col_count, char** records, [[maybe_unused]] char** col_names)
		{
			const auto harbors_ = static_cast<std::map<int, std::shared_ptr<Harbor>>*>(res);
			const int key = std::stoi(std::string{records[0]});
			harbors_->at(key)->distance(
				std::stoi(std::string{records[1]}
				));
			return 0;
		};
		const std::string query1 = std::format(
			"SELECT haven1_id, afstand "
			"FROM afstanden "
			"WHERE haven2_id == {}",
			harbor_id
		);

		const std::string query2 = std::format(
			"SELECT haven2_id, afstand "
			"FROM afstanden "
			"WHERE haven1_id == {}",
			harbor_id
		);
		exec_query(query1, cb, &harbors);
		exec_query(query2, cb, &harbors);
	}

	std::set<std::string> Sqlite_3::peculiarities(const int ship_id) const
	{
		auto cb = [](void* res, [[maybe_unused]] int col_count, char** records, [[maybe_unused]] char** col_names)
		{
			const auto peculiarites = static_cast<std::set<std::string>*>(res);
			peculiarites->emplace(
				records[0]
			);
			return 0;
		};
		const std::string query = std::format(
			"SELECT bijzonderheid "
			"FROM schepen_bijzonderheden "
			"JOIN bijzonderheden ON schepen_bijzonderheden.bijzonderheid_id == bijzonderheden.id "
			"WHERE schepen_bijzonderheden.schip_id == {}",
			ship_id
		);
		std::set<std::string> res;
		exec_query(query, cb, &res);
		return res;
	}

	void Sqlite_3::exec_query_ext(const std::string& query, const std::function<void(sqlite3_stmt*)>& cb) const
	{
		sqlite3_stmt* stmt = nullptr;
		if (sqlite3_prepare_v2(m_db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
		{
			sqlite3_finalize(stmt);
			throw std::runtime_error(sqlite3_errmsg(m_db));
		}

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			cb(stmt);
		}
		sqlite3_finalize(stmt);
	}
}
