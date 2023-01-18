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

		std::vector<std::shared_ptr<Harbor>> harbors() override;
		std::shared_ptr<Harbor> harbor(int id) override;
		std::vector<std::shared_ptr<Goods>> goods(int harbor_id) override;
	private:
		sqlite3* m_db{};
	};
}

#endif //SOC_FILESYSTEM_SQLITE_3_H




