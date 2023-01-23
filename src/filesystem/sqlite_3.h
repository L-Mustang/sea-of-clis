#ifndef SOC_FILESYSTEM_SQLITE_3_H
#define SOC_FILESYSTEM_SQLITE_3_H

#include <filesystem/filesystem.h>

namespace Soc::Filesystem
{
	/**
	 * @brief SQLite implementation of the Filesystem
	 */
	class Sqlite_3 final : public Filesystem
	{
	public:
		/**
		 * @brief Constructor
		 * @param db Path to the .db database file
		 */
		explicit Sqlite_3(const std::filesystem::path& db);
		~Sqlite_3() override;
		Sqlite_3(const Sqlite_3& other) = delete;
		Sqlite_3(Sqlite_3&& other) noexcept = delete;
		Sqlite_3& operator=(const Sqlite_3& other) = delete;
		Sqlite_3& operator=(Sqlite_3&& other) noexcept = delete;

		/**
		 * @brief Gets all harbors from the database
		 * @return Harbors
		 */
		[[nodiscard]] std::map<int, std::shared_ptr<Harbor>> harbors() const override;
		/**
		 * @brief Gets the goods for a specific harbor from the database
		 * @param harbor_id Harbor ID to get goods from
		 * @return Goods
		 */
		[[nodiscard]] std::map<int, std::shared_ptr<Goods>> goods(int harbor_id) const override;
		/**
		 * @brief Gets all ships from the database
		 * @return Ships
		 */
		[[nodiscard]] std::map<int, std::shared_ptr<Ship>> ships() const override;
		/**
		 * @brief Sets correct distances to Harbors from a given Harbor
		 * @param harbor_id Harbor ID
		 * @param harbors Updated Harbors
		 */
		void harbors_distances(int harbor_id, std::map<int, std::shared_ptr<Harbor>>& harbors) const override;
	private:
		sqlite3* m_db;

		/**
		 * @brief Gets the Peculiarities of a Ship
		 * @param ship_id Ship ID
		 * @return Set of Peculiarities
		 */
		[[nodiscard]] std::set<std::string> peculiarities(int ship_id) const;

		/**
		 * @brief Executes a query and processes results using a callback
		 * @tparam T Type of container used in the callback
		 * @param query Query to be executed
		 * @param cb Callback to be used for results processing
		 * @param res Container used for results
		 */
		template<typename T>
		void exec_query(const std::string& query, int(*cb)(void*, int, char**, char**), T* res) const
		{
			char* err = nullptr;
			sqlite3_exec(m_db, query.c_str(), cb, res, &err);
			if (err)
			{
				const std::string err_str{ err };
				sqlite3_free(err);
				throw std::runtime_error(err_str);
			}
		}
		/**
		 * @brief Executes a query and processes results using a callback, but maintains a pointer to sqlite3_stmt
		 * @param query Query to be executed
		 * @param cb Callback to be used for results processing
		 */
		void exec_query_ext(const std::string& query, const std::function<void(sqlite3_stmt*)>& cb) const;
	};
}

#endif //SOC_FILESYSTEM_SQLITE_3_H




