#include <filesystem/sqlite_3.h>

auto io = Soc::Filesystem::Sqlite_3(std::filesystem::path("db/handelsschepen.db"));

int main()
{
	io.harbor(1);
	return EXIT_SUCCESS;
}
