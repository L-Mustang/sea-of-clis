#include <logger.h>

namespace Soc
{
	Logger::Logger(std::filesystem::path log): m_filepath(std::move(log))
	{
		create_directory(m_filepath.parent_path());
		m_filestream.open(m_filepath /= std::format("log_{:%d_%m_%Y__%H_%M_%OS}.txt", std::chrono::system_clock::now()), std::ios::app);
	}

	Logger::~Logger()
	{
		m_filestream.close();
	}

	std::string Logger::to_upper(std::string str)
	{
		std::string res = std::move(str);
		std::ranges::transform(res, res.begin(), toupper);
		return res;
	}
}
