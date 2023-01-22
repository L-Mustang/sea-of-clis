#ifndef SOC_SHIP_TYPE_H
#define SOC_SHIP_TYPE_H

namespace Soc {
	enum class Ship_type : int
	{
		invalid = 0,
		normal = 1,
		light = 2,
		heavy = 3
	};

	inline std::ostream& operator <<(std::ostream& os, const Ship_type& obj)
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

#endif // SOC_SHIP_TYPE_H
