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

		std::map<int, std::shared_ptr<Harbor>> harbors() override;
		std::map<int, Goods> goods(int harbor_id) override;
	private:
		sqlite3* m_db;

		template<typename T>
		void get_results(const std::string& query, int(*cb)(void*, int, char**, char**), T* res)
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
	};
}

#endif //SOC_FILESYSTEM_SQLITE_3_H




