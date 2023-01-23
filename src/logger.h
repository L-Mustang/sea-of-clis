#ifndef SOC_LOGGER_H
#define SOC_LOGGER_H

namespace Soc
{
	class Logger {
	public:
		/**
		 * @brief Constructor
		 * @param log Filepath to a relative directory (does not have to exist)
		 */
		explicit Logger(std::filesystem::path log);
		~Logger();
		Logger(const Logger& other) = delete;
		Logger(Logger&& other) noexcept = delete;
		Logger& operator=(const Logger& other) = delete;
		Logger& operator=(Logger&& other) noexcept = delete;

		/**
		 * @brief Writes arguments to outputs
		 * @tparam Args Argument types, must implement operator<<
		 * @param args Arguments
		 */
		template <typename... Args>
		void write(const Args&... args)
		{
			((m_filestream << args << ' '), ...) << std::endl; // c++17 fold expression
			((std::cout << args << ' '), ...) << std::endl;
		} 
		/**
		 * @brief Writes map values and keys to outputs
		 * @tparam K Key type, must implement operator<<
		 * @tparam T Value type, must implement operator<<
		 * @param map Map
		 */
		template <typename K, typename T>
		void write(const std::map<K, T>& map)
		{
			int i = 1;
			for (auto& [key, val] : map)
			{
				m_filestream << std::right << std::setw(4) << std::format("[{}]", i) << val << std::endl;
				std::cout << std::left << std::setw(4) << std::format("[{}]", i) << val << std::endl;
				++i;
			}
		}
		/**
		 * @brief Writes map values and keys to outputs
		 * @tparam K Key type, must implement operator<<
		 * @tparam T Value type, must implement operator<<
		 * @param map Map
		 */
		template <typename K, typename T>
		void write(const std::map<K, std::shared_ptr<T>>& map)
		{
			int i = 1;
			for (auto& [key, val] : map)
			{
				m_filestream << std::right << std::setw(4) << std::format("[{}]", i) << *val << std::endl;
				std::cout << std::left << std::setw(4) << std::format("[{}]", i) << *val << std::endl;
				++i;
			}
		}
		/**
		 * @brief Waits for valid input
		 * @tparam T Input type, must implement operator>>
		 * @return Valid input
		 */
		template <typename T>
		[[nodiscard]] T read()
		{
			T res{};
			// it is important to ignore the rest of the line, since operator>>
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
		/**
		 * @brief Waits for valid input based on map keys. Valid means the map contains the input as key
		 * @tparam K Key type, must implement operator>>
		 * @tparam T Value type
		 * @return Valid input
		 */
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
		/**
		 * @brief Waits for enter key
		 */
		void wait()
		{
			write("[...]");
			std::cin.get();
		}
		/**
		 * @brief Waits for valid input within a given range
		 * @param max Upper bound
		 * @param min Lower bound
		 * @return Valid input
		 */
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
		/**
		 * @brief Clears the console
		 * @tparam F Invokable type
		 * @param cb Callback to be executed after clearing
		 */
		template<typename F>
		void clear(F& cb = [] {})
		{
			static_assert(std::is_invocable_v<F>, "Type F must be an invokable lambda");
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
		/**
		 * @brief Formats to US locale. Good for large currencies
		 * @tparam T Type to be formatted
		 * @param value Value to be formatted
		 * @return Formatted string
		 */
		template<typename T>
		static std::string format(T value)
		{
			// https://stackoverflow.com/a/7276879/10787114
		    std::stringstream ss;
		    ss.imbue(std::locale("en_US.UTF-8"));
		    ss << std::fixed << value;
		    return ss.str();
		}
		/**
		 * @brief Converts a string to uppercase
		 * @param str String to be converted
		 * @return Uppercase string
		 */
		static std::string to_upper(std::string str);

	private:
		std::filesystem::path m_filepath;
		std::ofstream m_filestream;
	};
}

#endif // SOC_LOGGER_H
