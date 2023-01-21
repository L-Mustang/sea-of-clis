#ifndef SOC_CANNONS_TYPE_H
#define SOC_CANNONS_TYPE_H

namespace Soc
{
	enum class Cannons_type : int
	{
		invalid,
		light,
		medium,
		heavy
	};

	inline std::ostream& operator<<(std::ostream& os, const Cannons_type& obj)
	{
		// https://stackoverflow.com/a/11421489/10787114
		return os << static_cast<std::underlying_type_t<Cannons_type>>(obj);
	}

	inline std::istream& operator>>(std::istream& is, Cannons_type& obj)
	{
		int res{};
		if (is >> res)
		{
			if (!(res < static_cast<int>(Cannons_type::invalid) || res > static_cast<int>(Cannons_type::heavy)))
			{
				obj = static_cast<Cannons_type>(res);
				return is;
			}
		}
		is.setstate(std::ios_base::failbit);
		return is;
	}
};

template <>
struct std::formatter<Soc::Cannons_type> : std::formatter<string>
{
	// https://stackoverflow.com/a/59914918/10787114
	auto format(Soc::Cannons_type obj, std::format_context& ctx) const
	{
		return formatter<std::string>::format(
			std::format("{}", static_cast<std::underlying_type_t<Soc::Cannons_type>>(obj)), ctx);
	}
};

#endif // SOC_CANNONS_TYPE_H
