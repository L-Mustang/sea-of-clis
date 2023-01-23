#ifndef SOC_CANNONS_TYPE_H
#define SOC_CANNONS_TYPE_H

namespace Soc
{
	enum class Cannons_type : int
	{
		invalid = 0,
		light = 1,
		medium = 2,
		heavy = 3
	};

	std::ostream& operator<<(std::ostream& os, const Cannons_type& obj);
	std::istream& operator>>(std::istream& is, Cannons_type& obj);
}

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
