#include <filesystem/sqlite_3.h>
#include <player.h>

auto io = Soc::Filesystem::Sqlite_3(std::filesystem::path("db/handelsschepen.db"));

int main()
{
	try
	{
		const Soc::Player player{ std::make_unique<Soc::Filesystem::Sqlite_3>(std::filesystem::path("db/handelsschepen.db")) };
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
