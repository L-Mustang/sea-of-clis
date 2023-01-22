#include <filesystem/sqlite_3.h>
#include <game.h>

auto io = Soc::Filesystem::Sqlite_3(std::filesystem::path("db/handelsschepen.db"));

int main()
{
#ifdef USE_WIN32
#ifdef _WIN32
	SetConsoleTitleA("Sea Of CLIs");
#else
	std::cout << "\033]0;" << "Sea Of CLIs" << "\007";
#endif
#endif
	try
	{
		const Soc::Game player{ std::make_unique<Soc::Filesystem::Sqlite_3>(std::filesystem::path("db/handelsschepen.db")) };
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
