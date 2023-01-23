#include <ship_type.h>

namespace Soc
{
	std::ostream& operator<<(std::ostream& os, const Ship_type& obj)
	{
		switch (obj)
		{
		case Ship_type::invalid:
			{
				os << "Invalid";
				break;				
			}
		case Ship_type::normal:
			{
				os << "Normal";
				break;
			}
		case Ship_type::light:
			{
				os << "Light";
				break;
			}
		case Ship_type::heavy:
			{
				os << "Heavy";
				break;
			}
		}
		return os;
	}
}
