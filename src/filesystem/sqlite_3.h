#ifndef SOC_FILESYSTEM_SQLITE_3_H
#define SOC_FILESYSTEM_SQLITE_3_H

#include <filesystem/filesystem.h>

namespace Soc::Filesystem
{
	class Sqlite_3 final : public Filesystem
	{
	public:
		explicit Sqlite_3(const std::filesystem::path& db);
		~Sqlite_3() override;
		Sqlite_3(const Sqlite_3& other) = delete;
		Sqlite_3(Sqlite_3&& other) noexcept = delete;
		Sqlite_3& operator=(const Sqlite_3& other) = delete;
		Sqlite_3& operator=(Sqlite_3&& other) noexcept = delete;

		[[nodiscard]] std::map<int, std::shared_ptr<Harbor>> harbors() const override;
		[[nodiscard]] std::map<int, std::shared_ptr<Goods>> goods(int harbor_id) const override;
		[[nodiscard]] std::map<int, std::shared_ptr<Ship>> ships() const override;
		void harbors_distances(int harbor_id, std::map<int, std::shared_ptr<Harbor>>& harbors) const override;
	private:
		sqlite3* m_db;

		[[nodiscard]] std::set<std::string> peculiarities(int ship_id) const;

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

		void exec_query_ext(const std::string& query, const std::function<void(sqlite3_stmt*)>& cb) const;
	};
}

#endif //SOC_FILESYSTEM_SQLITE_3_H




