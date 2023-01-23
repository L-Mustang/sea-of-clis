#include <utility>

#ifndef SOC_LOGGER_H
#define SOC_LOGGER_H

namespace Soc
{
	class Logger {
	public:
		explicit Logger(std::filesystem::path log);
		~Logger();
		Logger(const Logger& other) = delete;
		Logger(Logger&& other) noexcept = delete;
		Logger& operator=(const Logger& other) = delete;
		Logger& operator=(Logger&& other) noexcept = delete;

		template <typename... Args>
		void write(const Args&... args)
		{
			((m_filestream << args << ' '), ...) << std::endl; // C++17 fold expression
			((std::cout << args << ' '), ...) << std::endl;
		} 

		template <typename K, typename T>
		void write(const std::map<K, T>& vec)
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
		void write(const std::map<K, std::shared_ptr<T>>& map)
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
			std::cin >> in;
			while (!std::cin || !(map.contains(in) || static_cast<int>(in) == 0)) {
				write("Incorrect input, try again");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> in;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			m_filestream << in << std::endl;
			return in;
		}

		void wait()
		{
			write("[...]");
			std::cin.get();
		}

		[[nodiscard]] int read(const int max, const int min = 0)
		{
			int res;
			std::cin >> res;
			while (!std::cin || res < min || res > max) {
				write("Incorrect input, try again");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> res;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			m_filestream << res << std::endl;
			return res;
		}

		template<typename F>
		void clear(F& cb = [](){})
		{
			static_assert(std::is_invocable_v<F>, "Type F must be an invocable lambda");
#ifdef USE_LIBS
			m_filestream << ("\n[CONSOLE CLEARED]\n") << std::endl;
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
#else // ^^^ windows / other os vvv
			std::cout << "\033[2J\033[1; 1H";
#endif // _WIN32
#endif // USE_LIBS
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

		static std::string to_upper(std::string str);

	private:
		std::filesystem::path m_filepath;
		std::ofstream m_filestream;
	};
}

#endif // SOC_LOGGER_H
