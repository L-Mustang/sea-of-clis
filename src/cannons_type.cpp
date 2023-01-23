#include <cannons_type.h>

namespace Soc
{
	std::ostream& operator<<(std::ostream& os, const Cannons_type& obj)
	{
		// https://stackoverflow.com/a/11421489/10787114
		return os << static_cast<std::underlying_type_t<Cannons_type>>(obj);
	}

	std::istream& operator>>(std::istream& is, Cannons_type& obj)
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
}
