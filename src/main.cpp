#include <filesystem/sqlite_3.h>
#include <game.h>

int main()
{
#ifdef USE_LIBS
#ifdef _WIN32
	SetConsoleTitleA("Sea Of CLIs");
#ifdef USE_CRT
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif // USE_CRT
#else // ^^^ windows / other vvv
	std::cout << "\033]0;" << "Sea Of CLIs" << "\007";
#endif // _WIN32
#endif // USE_LIBS
	try
	{
		//int* c_ptr = (int*)malloc(sizeof(int)); // uncomment for memory leak detection 
		//*c_ptr = 5;
		//const int* cxx_ptr = new int(5);

		//free(c_ptr); // uncomment along with above block for address sanitizer
		//delete cxx_ptr;
		//printf("%d%% \n", *c_ptr);
		//std::cout << *cxx_ptr << std::endl;

		const Soc::Game player{
			std::make_unique<Soc::Filesystem::Sqlite_3>(std::filesystem::path("db/handelsschepen.db"))
		};
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
