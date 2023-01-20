#ifndef SOC_LOGGER_H
#define SOC_LOGGER_H


namespace Soc
{

	class Logger {
	public:
		explicit Logger(std::filesystem::path log) : m_filepath(std::move(log))
		{
			create_directory(m_filepath.parent_path());
			m_filestream.open(m_filepath /= std::format("log_{:%d_%m_%Y__%H_%M_%OS}.txt", std::chrono::system_clock::now()), std::ios::app);
		}

		~Logger()
		{
			m_filestream.close();
		}

		template <typename... Args>
		void write(const Args&... args)
		{
			((m_filestream << args << ' '), ...) << std::endl;
			((std::cout << args << ' '), ...) << std::endl;
		}

		template <typename K, typename T>
		void write(std::map<K, T> vec)
		{
			int i = 1;
			for (auto& [key, val] : vec)
			{
				m_filestream << std::right << std::setw(4) << std::format("[{}]", i) << val << std::endl;
				std::cout << std::left << std::setw(4) << std::format("[{}]", i) << val << std::endl;
				++i;
			}
		}

		template <typename K, typename T>
		void write(std::map<K, std::shared_ptr<T>> map)
		{
			for (const auto& [key, val] : map)
			{
				m_filestream << std::left << std::setw(4) << std::format("[{}]", key) << *val << std::endl;
				std::cout << std::left << std::setw(4) << std::format("[{}]", key) << *val << std::endl;
			}
		}

		template <typename T>
		[[nodiscard]] T read()
		{
			T res{};
			// It is important to ignore the rest of the line, since operator>>
			// won't extract any data from the stream anymore as it is in a wrong format.
			// https://stackoverflow.com/a/12722150/10787114
			while (!(std::cin >> res)) {
				write("Incorrect input, try again");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			m_filestream << res << std::endl;
			return res;
		}

		template <typename K, typename T>
		[[nodiscard]] K read(const std::map<K, T>& map)
		{
			K in{};
			T res{};
			std::cin >> in;
			while (!std::cin || !(map.contains(in) || in == 0)) {
				write("Incorrect input, try again");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> in;
			}
			m_filestream << res << std::endl;
			return in;
		}

		[[nodiscard]] int read(int max, int min = 0)
		{
			int res;
			std::cin >> res;
			while (!std::cin || res < min || res > max) {
				write("Incorrect input, try again");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> res;
			}
			m_filestream << res << std::endl;
			return res;
		}

		template<typename F>
		void clear(F& cb = [](){})
		{
			static_assert(std::is_invocable_v<F>, "Type F must be an invocable lambda");
#ifdef USE_WIN32
			m_filestream << ("[CONSOLE CLEARED]") << std::endl;
#ifdef _WIN32
			constexpr COORD tl = { 0,0 };
			CONSOLE_SCREEN_BUFFER_INFO s;
			const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(console, &s);
			DWORD written;
			const DWORD cells = s.dwSize.X * s.dwSize.Y;
			FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
			FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
			SetConsoleCursorPosition(console, tl);
#else
			std::cout << "\033[2J\033[1; 1H";
#endif
#endif
			cb();
		}

		template<typename T>
		static std::string format(T value)
		{
			// https://stackoverflow.com/a/7276879/10787114
		    std::stringstream ss;
		    ss.imbue(std::locale("en_US.UTF-8"));
		    ss << std::fixed << value;
		    return ss.str();
		}

	private:
		std::filesystem::path m_filepath;
		std::ofstream m_filestream;
	};
}

#endif // SOC_LOGGER_H
